#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>

#define LINE_BUFFER 512

typedef struct {
    uint32_t end;
    uint32_t id;
    uint32_t tamanho_total;
    uint32_t tamanho_conteudo;
    uint8_t *conteudo;

    Bloco* prox;
    Bloco* ant;

} Bloco;

typedef struct {
    uint32_t tamanho_mem;
    uint32_t mem_livre; 
    Bloco *inicio;
} Memoria;

void inicializarMemoria(Memoria* m) {
    m->inicio = NULL;
    m->mem_livre = m->tamanho_mem;
}

int insertDump(char *filename)
{
    return 0;
}

int removeBloco(int id)
{
    return 0;
}

int defrag() {

    return 0;
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
    char line[LINE_BUFFER];

    FILE *img = fopen(ifile, "rb");
    uint8_t byte;
    Memoria* mem;
    

    if (fread(&mem->tamanho_mem, sizeof(uint32_t), 1, img) != 1) {
        fclose(img);
        return -1;
    }

    inicializarMemoria(mem);

    while (1)
    {
        Bloco* b = malloc(sizeof(Bloco));
        if(fread(&b->end, sizeof(uint32_t), 1, img) != 1) {
            free(b);
            break;
        }
        fread(&b->id, sizeof(uint32_t), 1, img);
        fread(&b->tamanho_total, sizeof(uint32_t), 1, img);
        fread(&b->tamanho_conteudo, sizeof(uint32_t), 1, img);
        
        b->conteudo = malloc(b->tamanho_conteudo);
        fread(b->conteudo, sizeof(uint8_t), b->tamanho_conteudo, img);
        b->prox = mem->inicio;
        b->ant = NULL;
        if(mem->inicio != NULL) {
            mem->inicio->ant = b;
        }
        mem->inicio = b;
    }


    FILE *comandos = fopen(cfile, "r");
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
                insertDump(filename);
            }
        }
        if (strcmp(cmd, "DEFRAG") == 0)
        {
        }
        else if (strcmp(cmd, "REMOVE") == 0)
        {
            int id;
            if (sscanf(line, "REMOVE %d", &id) == 1)
            {
                removeBloco(id);
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

                printf("[INPUT] ID: %d, Hex: 0x%X, Texto: '%s'\n", id, hex_val, texto);
            }
        }
    }
    printf("\n%s %s %s %d\n", cfile, ifile, sfile, threads);

    return 0;
}
