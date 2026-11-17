#define _GNU_SOURCE /* [MUDANCA 1] necessario p/ ftruncate com -std=c11 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/sysinfo.h> /* get_nprocs */
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

typedef struct BlocoLivre
{
    uint32_t end;
    uint32_t tamanho;
    struct BlocoLivre *prox;
    struct BlocoLivre *ant;
} BlocoLivre;
typedef struct
{
    uint32_t tamanho_mem;
    uint32_t mem_livre;
    int nBlocos;
    int maxBlocos; /* [MUDANCA 2] tamanho do vetor vecBlocos */

    Bloco **vecBlocos;
    BlocoLivre *inicioLivres;
} Memoria;

void inicializarMemoria(Memoria *m)
{
    /* [MUDANCA 2] /4 em vez de /16: os blocos podem ter menos de 16 bytes
       (ex.: total 13), entao /16 podia estourar o vetor. calloc ja zera. */
    int maxBlocos = (m->tamanho_mem / 4) + 16 + m->maxBlocos; /* + maior id da imagem */
    m->maxBlocos = maxBlocos;
    m->vecBlocos = (Bloco **)calloc(maxBlocos, sizeof(Bloco *));
    m->nBlocos = 0;
    m->mem_livre = m->tamanho_mem;
    m->inicioLivres = NULL;
}
int encontrar_menor_id_livre(Memoria *mem)
{
    for (int id = 1; id < mem->maxBlocos; id++)
    {
        if (mem->vecBlocos[id] == NULL)
        {
            return id;
        }
    }
    return -1;
}

/* [MUDANCA 3] lista de livres ordenada por (tamanho, endereco):
   o desempate pelo MENOR ENDERECO era o que faltava. */
static int livre_vem_antes(BlocoLivre *a, BlocoLivre *b)
{
    return a->tamanho < b->tamanho || (a->tamanho == b->tamanho && a->end < b->end);
}

void inserir_bloco_livre_ordenado(Memoria *mem, BlocoLivre *novo)
{

    if (mem->inicioLivres == NULL)
    {
        mem->inicioLivres = novo;
        novo->prox = NULL;
        novo->ant = NULL;
        return;
    }

    if (livre_vem_antes(novo, mem->inicioLivres))
    {
        novo->prox = mem->inicioLivres;
        novo->ant = NULL;
        mem->inicioLivres->ant = novo;
        mem->inicioLivres = novo;
        return;
    }

    BlocoLivre *atual = mem->inicioLivres;
    while (atual->prox != NULL && livre_vem_antes(atual->prox, novo))
    {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    novo->ant = atual;

    if (atual->prox != NULL)
    {
        atual->prox->ant = novo;
    }
    atual->prox = novo;
}

static void desligar_livre(Memoria *mem, BlocoLivre *l)
{
    if (l->ant != NULL)
        l->ant->prox = l->prox;
    else
        mem->inicioLivres = l->prox;
    if (l->prox != NULL)
        l->prox->ant = l->ant;
}

/* [MUDANCA 4] blocos ordenados por endereco (o arquivo de imagem exige
   essa ordem; o defrag tambem usa). Substitui o "for i <= nBlocos". */
static int compararPorEnd(const void *a, const void *b)
{
    const Bloco *x = *(const Bloco **)a;
    const Bloco *y = *(const Bloco **)b;
    if (x->end < y->end)
        return -1;
    if (x->end > y->end)
        return 1;
    return 0;
}

static Bloco **obterBlocosOrdenados(Memoria *mem, int *qtd)
{
    Bloco **ord = (Bloco **)malloc(sizeof(Bloco *) * (mem->maxBlocos));
    int n = 0;
    for (int i = 0; i < mem->maxBlocos; i++)
        if (mem->vecBlocos[i] != NULL)
            ord[n++] = mem->vecBlocos[i];
    qsort(ord, n, sizeof(Bloco *), compararPorEnd);
    *qtd = n;
    return ord;
}

/* [MUDANCA 14] printStats para debug (so e chamado se compilar com -DDEBUG) */
void printStats(Memoria *mem)
{
    printf("total:%u, memlivre:%u\n", mem->tamanho_mem, mem->mem_livre);
    for (int i = 0; i < mem->maxBlocos; i++)
    {
        Bloco *p = mem->vecBlocos[i];
        if (p)
        {
            printf("end: %u, id: %u, tamtotal: %u, tam cont: %u pos: %d\n",
                   p->end, p->id, p->tamanho_total, p->tamanho_conteudo, i);
            // printf("conteudo: ");
            // for (uint32_t o = 0; o < p->tamanho_conteudo; o++)
            // {
            //     printf("%02X ", *(p->conteudo + o));
            // }
            // printf("\n");
        }
    }
    printf("---------------livres---------------\n");
    BlocoLivre *b = mem->inicioLivres;
    while (b)
    {
        printf("end: %u, tam: %u,\n", b->end, b->tamanho);
        b = b->prox;
    }
}

void salvarImg(char *arq, Memoria *mem)
{
    if (mem == NULL)
        return;

    int count = 0;
    Bloco **ord = obterBlocosOrdenados(mem, &count);

    /* [MUDANCA 5] omite os zeros finais do conteudo (exigencia 1) e calcula
       o tamanho REAL do arquivo (cabecalho + conteudo de cada bloco). */
    size_t tamanho_arquivo = sizeof(uint32_t);
    for (int i = 0; i < count; i++)
    {
        Bloco *b = ord[i];
        while (b->tamanho_conteudo > 0 && b->conteudo[b->tamanho_conteudo - 1] == 0)
            b->tamanho_conteudo--;
        tamanho_arquivo += sizeof(Header) + b->tamanho_conteudo;
    }

    int fd = open(arq, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
    {
        perror("Erro ao abrir arquivo de saída");
        free(ord);
        return;
    }
    if (ftruncate(fd, tamanho_arquivo) == -1)
    {
        perror("Erro na alocação");
        close(fd);
        free(ord);
        return;
    }

    uint8_t *data = mmap(NULL, tamanho_arquivo, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED)
    {
        perror("Erro no mmap de escrita");
        close(fd);
        free(ord);
        return;
    }

    memcpy(data, &mem->tamanho_mem, sizeof(uint32_t));
    size_t offset = sizeof(uint32_t);
    for (int i = 0; i < count; i++)
    {
        Bloco *b = ord[i];
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

    munmap(data, tamanho_arquivo);
    close(fd);
    free(ord);
}

/* [MUDANCA 13] threads so em carregarImg: a copia dos conteudos dos blocos
   (mmap da imagem -> malloc de cada bloco) e dividida em fatias entre as threads. */
typedef struct
{
    Bloco **bl;
    uint8_t **src;
    int inicio;
    int fim;
} CopiaArgs;

void *copia_thread(void *arg)
{
    CopiaArgs *a = (CopiaArgs *)arg;
    for (int i = a->inicio; i < a->fim; i++)
    {
        if (a->bl[i]->tamanho_conteudo > 0)
            memcpy(a->bl[i]->conteudo, a->src[i], a->bl[i]->tamanho_conteudo);
    }
    return NULL;
}

void copiar_paralelo(Bloco **bl, uint8_t **src, int n, int threads)
{
    int T = threads;
    if (T <= 0) /* 0 = o programa decide */
    {
        T = get_nprocs();
        if (T < 1)
            T = 1;
        int util = n / 4096; /* trabalho minimo por thread */
        if (util < 1)
            util = 1;
        if (T > util)
            T = util;
    }

    pthread_t *th = (pthread_t *)malloc(sizeof(pthread_t) * T);
    CopiaArgs *args = (CopiaArgs *)malloc(sizeof(CopiaArgs) * T);
    char *criada = (char *)calloc(T, 1);

    for (int t = 0; t < T; t++)
    {
        args[t].bl = bl;
        args[t].src = src;
        args[t].inicio = (int)(((int64_t)n * t) / T);
        args[t].fim = (int)(((int64_t)n * (t + 1)) / T);
        criada[t] = (pthread_create(&th[t], NULL, copia_thread, &args[t]) == 0);
        if (!criada[t])
            copia_thread(&args[t]); /* se falhar, copia na propria main */
    }
    for (int t = 0; t < T; t++)
        if (criada[t])
            pthread_join(th[t], NULL);

    free(th);
    free(args);
    free(criada);
}

void carregarImg(char *arq, Memoria *mem, int threads)
{

    int fd = open(arq, O_RDONLY);
    if (fd == -1)
    {
        perror("Erro ao abrir arquivo de imagem");
        exit(1);
    }
    struct stat sb;
    fstat(fd, &sb);
    size_t tamanho_arquivo = sb.st_size;
    uint8_t *data = mmap(NULL, tamanho_arquivo, PROT_READ, MAP_PRIVATE, fd, 0);
    memcpy(&mem->tamanho_mem, data, 4); // primeiro ponteiro

    /* [MUDANCA 2b] pre-varredura: descobre o maior id da imagem (ids podem ser
       esparsos), para que vecBlocos sempre comporte todos os ids */
    uint32_t maior_id = 0;
    for (size_t o = sizeof(uint32_t); o + sizeof(Header) <= tamanho_arquivo;)
    {
        Header hh;
        memcpy(&hh, data + o, sizeof(Header));
        if (hh.tamanho_total == 0)
            break;
        if (hh.id > maior_id)
            maior_id = hh.id;
        o += sizeof(Header) + hh.tamanho_conteudo;
    }
    mem->maxBlocos = (int)maior_id;
    inicializarMemoria(mem);
    Bloco **bl = (Bloco **)malloc(sizeof(Bloco *) * mem->maxBlocos);
    uint8_t **src = (uint8_t **)malloc(sizeof(uint8_t *) * mem->maxBlocos);
    int nCopias = 0;
    size_t offset = sizeof(uint32_t);

    uint32_t endereco_esperado = 0;

    while (offset < tamanho_arquivo)
    {
        Header hdr; /* memcpy: evita ponteiro desalinhado */
        memcpy(&hdr, data + offset, sizeof(Header));
        Header *h = &hdr;
        if (h->tamanho_total == 0)
        {
            break;
        }
        if (h->end > endereco_esperado)
        {
            uint32_t tam_livre = h->end - endereco_esperado;

            BlocoLivre *livre = (BlocoLivre *)malloc(sizeof(BlocoLivre));
            livre->end = endereco_esperado;
            livre->tamanho = tam_livre;
            livre->prox = NULL;
            livre->ant = NULL;

            inserir_bloco_livre_ordenado(mem, livre);
        }

        Bloco *b = malloc(sizeof(Bloco));
        b->end = h->end;
        b->id = h->id;
        b->tamanho_total = h->tamanho_total;
        b->tamanho_conteudo = h->tamanho_conteudo;
        b->conteudo = malloc(b->tamanho_conteudo);

        mem->vecBlocos[b->id] = b;

        bl[nCopias] = b; /* a copia do conteudo e feita depois, em paralelo */
        src[nCopias] = data + offset + sizeof(Header);
        nCopias++;
        mem->mem_livre -= b->tamanho_total;
        endereco_esperado = h->end + h->tamanho_total;
        offset += sizeof(Header) + h->tamanho_conteudo;
        mem->nBlocos++;
    }

    if (endereco_esperado < mem->tamanho_mem)
    {
        uint32_t tam_livre_final = mem->tamanho_mem - endereco_esperado;

        BlocoLivre *livre_final = (BlocoLivre *)malloc(sizeof(BlocoLivre));
        livre_final->end = endereco_esperado;
        livre_final->tamanho = tam_livre_final;
        livre_final->prox = NULL;
        livre_final->ant = NULL;

        inserir_bloco_livre_ordenado(mem, livre_final);
    }

    copiar_paralelo(bl, src, nCopias, threads);
    free(bl);
    free(src);

    munmap(data, tamanho_arquivo);
    close(fd);
}

/* [MUDANCA 6] defrag sequencial: ordena por endereco, empilha os blocos
   no inicio e recria um unico buraco livre no final. Sem threads. */
Memoria *defrag(Memoria *mem, int nBlocos, int numThreads)
{
    (void)nBlocos;
    (void)numThreads;
    if (mem == NULL)
        return mem;

    int n = 0;
    Bloco **ord = obterBlocosOrdenados(mem, &n);
    uint32_t pos = 0;
    for (int i = 0; i < n; i++)
    {
        ord[i]->end = pos;
        pos += ord[i]->tamanho_total;
    }
    free(ord);

    BlocoLivre *curr = mem->inicioLivres;
    while (curr != NULL)
    {
        BlocoLivre *temp = curr;
        curr = curr->prox;
        free(temp);
    }
    mem->inicioLivres = NULL;

    if (pos < mem->tamanho_mem)
    {
        BlocoLivre *livre_unico = (BlocoLivre *)malloc(sizeof(BlocoLivre));
        livre_unico->end = pos;
        livre_unico->tamanho = mem->tamanho_mem - pos;
        livre_unico->prox = NULL;
        livre_unico->ant = NULL;
        mem->inicioLivres = livre_unico;
    }
    return mem;
}

static BlocoLivre *buscar_livre(Memoria *mem, uint32_t tam)
{
    /* lista ordenada por (tamanho, endereco): o primeiro que couber e o Best Fit */
    BlocoLivre *b = mem->inicioLivres;
    while (b != NULL && b->tamanho < tam)
        b = b->prox;
    return b;
}

void insertDump(char *arq, Memoria *mem, int threads)
{
    int fd = open(arq, O_RDONLY);
    if (fd == -1)
    {
        return;
    }

    /* [MUDANCA 7] formato do dump: <total(4)><conteudo(4)><bytes do conteudo> */
    struct stat sb;
    fstat(fd, &sb);
    size_t tam_arq = (size_t)sb.st_size;
    if (tam_arq < 8)
    {
        close(fd);
        return;
    }
    uint8_t *data = mmap(NULL, tam_arq, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED)
    {
        close(fd);
        return;
    }

    uint32_t tamanho_total, tamanho_conteudo;
    memcpy(&tamanho_total, data, 4);
    memcpy(&tamanho_conteudo, data + 4, 4);
    if (tamanho_conteudo > tam_arq - 8)
        tamanho_conteudo = (uint32_t)(tam_arq - 8);
    if (tamanho_conteudo > tamanho_total)
        tamanho_conteudo = tamanho_total;

    /* sem espaco livre total: falha em silencio, SEM desfragmentar */
    if (tamanho_total == 0 || mem->mem_livre < tamanho_total)
    {
        munmap(data, tam_arq);
        close(fd);
        return;
    }
    int novo_id = encontrar_menor_id_livre(mem);
    if (novo_id == -1)
    {
        munmap(data, tam_arq);
        close(fd);
        return;
    }

    BlocoLivre *b = buscar_livre(mem, tamanho_total);

    /* [MUDANCA 8] defrag compulsoria: ha espaco total mas nao contiguo */
    if (b == NULL)
    {
        defrag(mem, mem->nBlocos, threads);
        b = buscar_livre(mem, tamanho_total);
    }
    if (b == NULL)
    {
        munmap(data, tam_arq);
        close(fd);
        return;
    }

    Bloco *novo = (Bloco *)malloc(sizeof(Bloco));
    novo->id = novo_id;
    novo->end = b->end;
    novo->tamanho_total = tamanho_total;
    novo->tamanho_conteudo = tamanho_conteudo;
    novo->conteudo = (uint8_t *)malloc(tamanho_conteudo);

    memcpy(novo->conteudo, data + 8, tamanho_conteudo);

    munmap(data, tam_arq);
    close(fd);

    mem->vecBlocos[novo_id] = novo;
    mem->mem_livre -= tamanho_total;
    mem->nBlocos++;

    desligar_livre(mem, b);
    if (b->tamanho == tamanho_total)
    {
        free(b);
    }
    else
    {
        b->end += tamanho_total;
        b->tamanho -= tamanho_total;
        b->prox = NULL;
        b->ant = NULL;

        inserir_bloco_livre_ordenado(mem, b);
    }
}

int removeBloco(int id, Memoria *mem)
{
    if (id <= 0 || id >= mem->maxBlocos)
        return 0;
    if (mem->vecBlocos[id])
    {
        Bloco *b = mem->vecBlocos[id];
        mem->mem_livre += b->tamanho_total;

        /* [MUDANCA 9] coalescencia: funde com buracos vizinhos
           (um que termina onde o bloco comeca, outro que comeca onde ele termina) */
        uint32_t ini = b->end;
        uint32_t tam = b->tamanho_total;
        BlocoLivre *l = mem->inicioLivres;
        while (l != NULL)
        {
            BlocoLivre *prox = l->prox;
            if (l->end + l->tamanho == b->end)
            {
                ini = l->end;
                tam += l->tamanho;
                desligar_livre(mem, l);
                free(l);
            }
            else if (l->end == b->end + b->tamanho_total)
            {
                tam += l->tamanho;
                desligar_livre(mem, l);
                free(l);
            }
            l = prox;
        }

        BlocoLivre *novo = (BlocoLivre *)malloc(sizeof(BlocoLivre));
        novo->end = ini;
        novo->tamanho = tam;
        novo->prox = NULL;
        novo->ant = NULL;

        inserir_bloco_livre_ordenado(mem, novo);
        if (b->conteudo != NULL)
        {
            free(b->conteudo);
        }
        free(b);
        mem->vecBlocos[id] = NULL;
    }
    return 0;
}

/* [MUDANCA 10] comando INPUT, que antes nao fazia nada */
void execInput(int id, unsigned int offset, char *text, Memoria *mem)
{
    if (!text || id <= 0 || id >= mem->maxBlocos || !mem->vecBlocos[id])
    {
        return;
    }
    Bloco *b = mem->vecBlocos[id];
    size_t len = strlen(text);
    if (len == 0 || (uint64_t)offset + len > b->tamanho_total)
    {
        return;
    }

    uint32_t fim = offset + (uint32_t)len;
    if (fim > b->tamanho_conteudo)
    {
        uint8_t *novo_ptr = realloc(b->conteudo, fim);
        if (!novo_ptr)
            return;
        /* bytes entre o conteudo antigo e o offset devem ser 0x00 */
        if (offset > b->tamanho_conteudo)
            memset(novo_ptr + b->tamanho_conteudo, 0, offset - b->tamanho_conteudo);
        b->conteudo = novo_ptr;
        b->tamanho_conteudo = fim;
    }
    memcpy(b->conteudo + offset, text, len);
}

void executarCmds(FILE *comandos, Memoria *mem, int threads)
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
                insertDump(filename, mem, threads);
            }
        }
        else if (strcmp(cmd, "DEFRAG") == 0)
        {
            defrag(mem, mem->nBlocos, threads); /* [MUDANCA 11] estava comentado */
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
            if (sscanf(line, "INPUT %d %i%n", &id, &hex_val, &offset) == 2)
            {
                char *texto = line + offset;
                if (*texto == ' ')
                    texto++;
                texto[strcspn(texto, "\r\n")] = '\0';
                execInput(id, hex_val, texto, mem);
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

    carregarImg(ifile, mem, threads);

    FILE *comandos = fopen(cfile, "r");
    if (!comandos)
    {
        perror("Erro ao abrir arquivo de comandos");
        return 1;
    }
#ifdef DEBUG
    printStats(mem);
    printf("\n ---------------- depois dos comandos ---------------- \n");
#endif
    executarCmds(comandos, mem, threads);
    fclose(comandos);
#ifdef DEBUG
    printStats(mem);
#endif

    /* [MUDANCA 12] removidos os printStats, o defrag final nao pedido e o printf */
    salvarImg(sfile, mem);

    return 0;
}