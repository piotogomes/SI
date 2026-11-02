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
    Bloco *inicio;
} Memoria;

void printStats(Memoria *mem)
{
    Bloco *p = mem->inicio;
    while (p)
    {
        printf("id:%d\n", p->id);

        // printf("end: %d, id: %d, tamtotal: %d, tam cont: %d\n", p->end, p->id, p->tamanho_total, p->tamanho_conteudo);
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
    m->mem_livre = m->tamanho_mem;
}

void carregarImg(char *arq, Memoria *mem)
{

    int fd = open(arq, O_RDONLY);
    struct stat sb;
    fstat(fd, &sb);
    size_t tamanho_arquivo = sb.st_size;
    uint8_t *data = mmap(NULL, tamanho_arquivo, PROT_READ, MAP_PRIVATE, fd, 0);
    mem->tamanho_mem = *((uint32_t *)data);
    inicializarMemoria(mem);
    size_t offset = sizeof(uint32_t);

    while (offset < tamanho_arquivo)
    {
        Header *h = (Header *)(data + offset);
        Bloco *b = malloc(sizeof(Bloco));
        b->end = h->end;
        b->id = h->id;
        b->tamanho_total = h->tamanho_total;
        b->tamanho_conteudo = h->tamanho_conteudo;
        b->prox = mem->inicio;
        b->ant = NULL;
        b->conteudo = malloc(b->tamanho_conteudo);
        memcpy(b->conteudo, data + offset + sizeof(Header), b->tamanho_conteudo);
        mem->mem_livre -= b->tamanho_total;

        if (mem->inicio != NULL)
        {
            mem->inicio->ant = b;
        }
        mem->inicio = b;

        offset += sizeof(Header) + h->tamanho_conteudo;
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

int defrag(Memoria *mem)
{

    return 0;
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
            defrag(mem);
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

    printf("\n%s %s %s %d\n", cfile, ifile, sfile, threads);

    return 0;
}
