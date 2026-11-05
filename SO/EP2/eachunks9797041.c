#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define LINE_BUFFER 512

typedef struct
{
    uint32_t end;
    uint32_t id;
    uint32_t tamanho_total;
    uint32_t tamanho_conteudo;

} Header;

typedef struct s
{
    uint32_t end;
    uint32_t id;
    uint32_t tamanho_total;
    uint32_t tamanho_conteudo;
    uint8_t *conteudo;

} Bloco;

typedef struct
{
    uint32_t tamanho_mem;
    uint32_t mem_livre;
    int nBlocos;
    Bloco **vecBlocos;
} Memoria;

typedef struct
{
    Bloco **blocos;
    uint32_t *novos_ends;
    int inicio;
    int fim;
} DefragArgs;

void *defrag_thread(void *arg)
{
    DefragArgs *args = (DefragArgs *)arg;
    for (int i = args->inicio; i < args->fim; i++)
    {
        Bloco *b = args->blocos[i];
        if (b)
        {
            b->end = args->novos_ends[i];
            if (b->conteudo != NULL && b->tamanho_conteudo > 0)
            {
                uint8_t *novo_conteudo = malloc(b->tamanho_conteudo);
                memcpy(novo_conteudo, b->conteudo, b->tamanho_conteudo);

                free(b->conteudo);
                b->conteudo = novo_conteudo;
            }
        }
    }

    return NULL;
}

void printStats(Memoria *mem)
{

    for (int i = 0; i <= mem->nBlocos; i++)
    {
        Bloco *p = mem->vecBlocos[i];
        if (p)
        {
            printf("end: %d, id: %d, tamtotal: %d, tam cont: %d pos: %d\n", p->end, p->id, p->tamanho_total, p->tamanho_conteudo, i);
            // printf("conteudo: ");
            // for (int offset = 0; offset < p->tamanho_conteudo; offset++)
            // {
            //     printf("%02X ", *(p->conteudo + offset));
            // }
            // printf("\n");
        }
    }
    printf("total:%d, memlivre:%d\n", mem->tamanho_mem, mem->mem_livre);
}
void inicializarMemoria(Memoria *m)
{
    int maxBlocos = (m->tamanho_mem / sizeof(Header)) + 16;
    m->vecBlocos = (Bloco **)malloc(sizeof(Bloco *) * maxBlocos);
    for (int i = 0; i < maxBlocos; i++)
    {
        m->vecBlocos[i] = NULL;
    }
    m->nBlocos = 0;
    m->mem_livre = m->tamanho_mem;
}

void salvarImg(char *arq, Memoria *mem)
{
    if (mem == NULL)
        return;
    int fd = open(arq, O_RDWR | O_CREAT | O_TRUNC, 0666);
    int tamanho_arquivo = (sizeof(uint32_t) + mem->tamanho_mem - mem->mem_livre);
    if (fd == -1)
    {
        perror("Erro ao abrir arquivo de saída");
        return;
    }
    if (ftruncate(fd, tamanho_arquivo) == -1)
    {
        perror("Erro na alocação");
        close(fd);
        return;
    }

    uint8_t *data = mmap(NULL, tamanho_arquivo, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED)
    {
        perror("Erro no mmap de escrita");
        close(fd);
        return;
    }

    *((uint32_t *)data) = mem->tamanho_mem;
    size_t offset = sizeof(uint32_t);
    for (int i = 0; i <= mem->nBlocos; i++)
    {
        Bloco *b = mem->vecBlocos[i];
        if (b)
        {
            Header h;
            h.end = b->end;
            h.id = b->id;
            h.tamanho_total = b->tamanho_total;
            h.tamanho_conteudo = b->tamanho_conteudo;

            memcpy(data + offset, &h, sizeof(Header));
            if (b->conteudo != NULL && b->tamanho_conteudo > 0)
            {
                memcpy(data + offset + sizeof(Header), b->conteudo, b->tamanho_conteudo);
            }

            offset += b->tamanho_conteudo + sizeof(Header);
        }
    }

    munmap(data, sizeof(uint32_t) + mem->tamanho_mem - mem->mem_livre);
    close(fd);
}

void carregarImg(char *arq, Memoria *mem)
{

    int fd = open(arq, O_RDONLY);
    if (fd == -1)
    {
        perror("Erro ao abrir arquivo de imagem");
        return;
    }
    struct stat sb;
    fstat(fd, &sb);
    size_t tamanho_arquivo = sb.st_size;
    uint8_t *data = mmap(NULL, tamanho_arquivo, PROT_READ, MAP_PRIVATE, fd, 0);
    mem->tamanho_mem = *((uint32_t *)data); // primeiro ponteiro
    inicializarMemoria(mem);
    size_t offset = sizeof(uint32_t);
    while (offset < tamanho_arquivo)
    {
        Header *h = (Header *)(data + offset);
        if (h->tamanho_total == 0)
        {
            break;
        }
        Bloco *b = malloc(sizeof(Bloco));
        b->end = h->end;
        b->id = h->id;
        b->tamanho_total = h->tamanho_total;
        b->tamanho_conteudo = h->tamanho_conteudo;
        b->conteudo = malloc(b->tamanho_conteudo);

        mem->vecBlocos[b->id] = b;

        memcpy(b->conteudo, data + offset + sizeof(Header), b->tamanho_conteudo);
        mem->mem_livre -= (b->tamanho_conteudo + sizeof(Header));
        offset += sizeof(Header) + h->tamanho_conteudo;
        mem->nBlocos++;
    }
    munmap(data, tamanho_arquivo);
    close(fd);
}

int insertDump(char *filename, Memoria *mem)
{

    return 0;
}

int removeBloco(int id, Memoria *mem)
{
    if (mem->vecBlocos[id])
    {
        Bloco *b = mem->vecBlocos[id];
        mem->mem_livre += b->tamanho_total;
        if (b->conteudo != NULL)
        {
            free(b->conteudo);
        }
        free(b);
        mem->vecBlocos[id] = NULL;
    }
    return 0;
}

Memoria *defrag(Memoria *mem, int nBlocos, int numThreads)
{
    if (mem == NULL || nBlocos < 0)
        return mem;

    int total_ativos = 0;
    for (int i = 0; i <= nBlocos; i++)
    {
        if (mem->vecBlocos[i] != NULL)
        {
            total_ativos++;
        }
    }

    if (total_ativos == 0)
        return mem;

    if (numThreads > total_ativos)
        numThreads = total_ativos;
    if (numThreads <= 0)
        numThreads = 1;

    Bloco **bs = (Bloco **)malloc(total_ativos * sizeof(Bloco *));
    uint32_t *novos_ends = (uint32_t *)malloc(total_ativos * sizeof(uint32_t));

    uint32_t offset_atual = 0;
    int idx = 0;
    for (int i = 0; i <= nBlocos; i++)
    {
        if (mem->vecBlocos[i])
        {
            bs[idx] = mem->vecBlocos[i];
            novos_ends[idx] = offset_atual;
            offset_atual += mem->vecBlocos[i]->tamanho_total;
            idx++;
        }
    }

    pthread_t *threads = (pthread_t *)malloc(numThreads * sizeof(pthread_t));
    DefragArgs *w_args = (DefragArgs *)malloc(numThreads * sizeof(DefragArgs));

    int blocos_por_thread = total_ativos / numThreads;
    int resto = total_ativos % numThreads;
    int inicio_atual = 0;

    for (int i = 0; i < numThreads; i++)
    {
        w_args[i].blocos = bs;
        w_args[i].novos_ends = novos_ends;
        w_args[i].inicio = inicio_atual;

        int carga_desta_thread = blocos_por_thread + (i < resto ? 1 : 0);
        inicio_atual += carga_desta_thread;

        w_args[i].fim = inicio_atual;

        pthread_create(&threads[i], NULL, defrag_thread, (void *)&w_args[i]);
    }

    for (int i = 0; i < numThreads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    free(bs);
    free(novos_ends);
    free(threads);
    free(w_args);

    return mem;
}

void executarCmds(FILE *comandos, Memoria *mem)
{
    char line[LINE_BUFFER];
    while (fgets(line, LINE_BUFFER, comandos) != NULL)
    {
        char cmd[32];

        if (sscanf(line, "%31s", cmd) != 1)
            continue;

        if (strcmp(cmd, "INSERT") == 0)
        {
            char filename[256];
            if (sscanf(line, "INSERT %255s", filename) == 1)
            {
                insertDump(filename, mem);
            }
        }
        else if (strcmp(cmd, "DEFRAG") == 0)
        {
            // defrag(mem, 0, 1);
        }
        else if (strcmp(cmd, "REMOVE") == 0)
        {
            int id;
            if (sscanf(line, "REMOVE %d", &id) == 1)
            {
                // removeBloco(id, mem);
            }
        }
        else if (strcmp(cmd, "INPUT") == 0)
        {
            int id;
            unsigned int hex_val;
            int offset = 0;
            if (sscanf(line, "INPUT %d %i %n", &id, &hex_val, &offset) == 2)
            {
                char *texto = line + offset;
                texto[strcspn(texto, "\n")] = '\0';
            }
        }
    }
}

int main(int argv, char **argc)
{

    if (argv != 5)
    {
        printf("Usage: ./eachunks9797041 <comandos> <imagem> <saída> <threads>\n");
        return -1;
    }
    char *cfile = argc[1];
    char *ifile = argc[2];
    char *sfile = argc[3];
    int threads = atoi(argc[4]);
    Memoria *mem = (Memoria *)malloc(sizeof(Memoria));

    carregarImg(ifile, mem);

    FILE *comandos = fopen(cfile, "r");
    executarCmds(comandos, mem);

    defrag(mem, mem->nBlocos, threads);
    printStats(mem);
    removeBloco(3, mem);
    printStats(mem);
    
    defrag(mem, mem->nBlocos, threads);
    
    printf("%s %d\n", sfile, threads);
    printStats(mem);
    salvarImg(sfile, mem);

    free(mem);
    return 0;
}
