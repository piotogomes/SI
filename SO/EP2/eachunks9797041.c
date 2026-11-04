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

    struct s *prox;
    struct s *ant;

} Bloco;

typedef struct
{
    uint32_t tamanho_mem;
    uint32_t mem_livre;
    int nBlocos;
    Bloco *inicio;
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
        b->end = args->novos_ends[i];
        if (b->conteudo != NULL && b->tamanho_conteudo > 0)
        {
            uint8_t *novo_conteudo = malloc(b->tamanho_conteudo);
            memcpy(novo_conteudo, b->conteudo, b->tamanho_conteudo);

            free(b->conteudo);
            b->conteudo = novo_conteudo;
        }
    }

    return NULL;
}

void printStats(Memoria *mem)
{
    Bloco *p = mem->inicio;
    printf("total:%d, memlivre:%d\n", mem->tamanho_mem, mem->mem_livre);
    while (p)
    {
        printf("end: %d, id: %d, tamtotal: %d, tam cont: %d\n", p->end, p->id, p->tamanho_total, p->tamanho_conteudo);
        // printf("conteudo: ");
        // for (int offset = 0; offset < p->tamanho_conteudo; offset++)
        // {
        //     printf("%02X ", *(p->conteudo + offset));
        // }
        // printf("\n");
        p = p->prox;
    }
}
void inicializarMemoria(Memoria *m)
{
    m->inicio = NULL;
    m->nBlocos = 0;
    m->mem_livre = m->tamanho_mem;
}

void salvarImg(char *arq, Memoria *mem)
{
    if (mem == NULL)
        return;
    int fd = open(arq, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
    {
        perror("Erro ao abrir arquivo de saída");
        return;
    }
    if (ftruncate(fd, (mem->tamanho_mem - mem->mem_livre)) == -1)
    {
        perror("Erro na alocação");
        close(fd);
        return;
    }

    uint8_t *data = mmap(NULL, (mem->tamanho_mem - mem->mem_livre), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED)
    {
        perror("Erro no mmap de escrita");
        close(fd);
        return;
    }

    *((uint32_t *)data) = mem->tamanho_mem;
    size_t offset = sizeof(uint32_t);
    Bloco *b = mem->inicio;
    while (b != NULL)
    {

        Header h;
        h.end = b->end;
        h.id = b->id;
        h.tamanho_total = b->tamanho_total;
        h.tamanho_conteudo = b->tamanho_conteudo;


        memcpy(data + offset, &h, sizeof(Header));
        offset += sizeof(Header);


        if (b->conteudo != NULL && b->tamanho_conteudo > 0)
        {
            memcpy(data + offset, b->conteudo, b->tamanho_conteudo);
        }

        offset += b->tamanho_conteudo;
        b = b->prox;
    }

    munmap(data, mem->tamanho_mem);
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
    mem->tamanho_mem = *((uint32_t *)data);
    inicializarMemoria(mem);
    size_t offset = sizeof(uint32_t);
    Bloco *aux = NULL;

    while (offset < tamanho_arquivo)
    {
        Header *h = (Header *)(data + offset);
        if (h->tamanho_total == 0) {
            break; 
        }
        Bloco *b = malloc(sizeof(Bloco));
        b->end = h->end;
        b->id = h->id;
        b->tamanho_total = h->tamanho_total;
        b->tamanho_conteudo = h->tamanho_conteudo;
        b->prox = NULL;
        b->conteudo = malloc(b->tamanho_conteudo);
        memcpy(b->conteudo, data + offset + sizeof(Header), b->tamanho_conteudo);
        mem->mem_livre -= b->tamanho_total;
        b->ant = aux;
        if (mem->inicio == NULL)
        {
            mem->inicio = b;
        }
        else
        {
            aux->prox = b;
        }
        aux = b;
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
    return 0;
}

Memoria *defrag(Memoria *mem, int nBlocos, int numThreads)
{
    if (mem == NULL || mem->inicio == NULL || nBlocos <= 0)
        return mem;
    if (numThreads > nBlocos)
        numThreads = nBlocos;
    if (numThreads <= 0)
        numThreads = 1;
    Bloco **bs = (Bloco **)malloc(nBlocos * sizeof(Bloco *));
    uint32_t *novos_ends = (uint32_t *)malloc(nBlocos * sizeof(uint32_t));
    Bloco *p = mem->inicio;
    uint32_t offset_atual = 0;
    for (int i = 0; i < nBlocos; i++)
    {
        bs[i] = p;
        novos_ends[i] = offset_atual;

        offset_atual += p->tamanho_total;
        p = p->prox;
    }
    mem->mem_livre = mem->tamanho_mem - offset_atual;

    pthread_t *threads = (pthread_t *)malloc(numThreads * sizeof(pthread_t));
    DefragArgs *w_args = (DefragArgs *)malloc(numThreads * sizeof(DefragArgs));

    int blocos_por_thread = nBlocos / numThreads;
    int resto = nBlocos % numThreads;
    int idx_atual = 0;

    for (int i = 0; i < numThreads; i++)
    {
        w_args[i].blocos = bs;
        w_args[i].novos_ends = novos_ends;
        w_args[i].inicio = idx_atual;

        int carga_desta_thread = blocos_por_thread + (i < resto ? 1 : 0);
        idx_atual += carga_desta_thread;

        w_args[i].fim = idx_atual;

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
            defrag(mem, 0, 1);
        }
        else if (strcmp(cmd, "REMOVE") == 0)
        {
            int id;
            if (sscanf(line, "REMOVE %d", &id) == 1)
            {
                removeBloco(id, mem);
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
    printStats(mem);
    defrag(mem, 5, threads);
    salvarImg(sfile, mem);
    printf("\n%s %s %s %d\n", cfile, ifile, sfile, threads);

    return 0;
}
