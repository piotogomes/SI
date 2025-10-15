#include <stdbool.h>


#define MAX 1000
#define NP 5

// LISTA SEQUENCIAL
typedef struct {
    int chave;

} RegistroSeq;

typedef struct {
    RegistroSeq A[MAX];
    int tam;
} ListaSeq;


void ls_inicializar(ListaSeq* l);
void ls_exibir(ListaSeq* l);
bool ls_inserir(ListaSeq* l, int ch);
bool ls_excluir(ListaSeq* l, int ch);
int ls_buscaBin(ListaSeq* l, int ch);

// LISTA LIGADA ESTATICA

typedef struct {
    int chave;
    int prox;
} RegistroLigEst;

typedef struct {
    RegistroLigEst A[MAX];
    int inicio;
    int dispo;
} ListaLigEst;

void lle_inicializar(ListaLigEst* l);
void lle_exibir(ListaLigEst *l);
int  lle_busca_f(ListaLigEst *l, int ch, int* ant);
int  lle_busca(ListaLigEst *l, int ch);
void lle_liberarDispo(ListaLigEst* l, int j);
bool lle_excluir(ListaLigEst *l, int ch);
int  lle_obterDispo(ListaLigEst* l);
bool lle_inserir(ListaLigEst* l, int ch);
bool lle_trocarPosProx(ListaLigEst* l, int ch);
bool lle_verificarListaLigEstIguais(ListaLigEst* l1, ListaLigEst* l2);
bool lle_excluirDupes(ListaLigEst* l, int ch);

// LISTA LIGADA DINAMICA SIMPLES

typedef struct s{
    int chave;
    struct s* prox;
} NOSim;

typedef struct {
    NOSim* inicio;
} ListaLDS; // ligada dinamica simples

void llds_inicializar(ListaLDS* l);
void llds_exibir(ListaLDS* l);
NOSim* llds_busca(ListaLDS *l, int ch, NOSim** ant);
bool llds_excluir(ListaLDS *l, int ch);
bool llds_inserir(ListaLDS* l, int ch);


// FILAS

typedef struct s{
    int chave;
    struct s* prox;
} NOfila;

typedef struct {
    NOfila* inicio;
    NOfila* fim;
} Fila; // Fila din

typedef struct s{
    int chave;
}NOFilaEst;

typedef struct {
    NOFilaEst A[MAX];
    int inicio;
    int fim;
} FilaEst; // Fila est

typedef struct s{
    int chave;
    struct s* prox;
    struct s* ant;
}NOFilaDupla;

typedef struct {
    NOFilaDupla* inicio1;
    NOFilaDupla* inicio2;
} FilaDupla; // Fila din


void fila_inicializar(Fila* f);
void fila_anexar(Fila* f, int ch);
int fila_retornar(Fila* f);
void filaEst_inicializar(FilaEst* f);
bool filaEst_anexar(FilaEst* f, int ch);
int filaEst_retornar(FilaEst* f);
void filaDu_inicializar(FilaDupla* f);
void filaDu_anexar1(FilaDupla* f, int ch);
int filaDu_retornar1(FilaDupla* f);
void filaDu_anexar2(FilaDupla* f, int ch);
int filaDu_retornar2(FilaDupla* f);

// PILHAS

typedef struct s{
    int chave;
    struct s* prox;
} NOpilha;

typedef struct {
    NOpilha* topo;
} Pilha; // pilha din

typedef struct s{
    int chave;
} NOPilhaEst;

typedef struct {
    NOPilhaEst A[MAX];
    int topo;
} PilhaEst; // pilha est

typedef struct {
    NOPilhaEst A[MAX];
    int topo1;
    int topo2;
} PilhaDup; // pilha dupla no mesmo vetor

typedef struct {
    NOPilhaEst A[MAX];
    int topo[NP + 1];
    int base[NP + 1];
} NPilhas; // pilha dupla no mesmo vetor



void pilha_inicializar(Pilha* p);
void pilha_inserir(Pilha* p, int ch);
int pilha_retornar(Pilha* p);
void pilhaEst_inicializar(PilhaEst* p);
void pilhaEst_inserir(PilhaEst* p, int ch);
int pilhaEst_retornar(PilhaEst* p);
void pilhaDup_inicializar(PilhaDup* p);
void pilhaDup_inserir1(PilhaDup* p, int ch);
int pilhaDup_retornar1(PilhaDup* p);
void pilhaDup_inserir2(PilhaDup* pi, int ch);
int pilhaDup_retornar2(PilhaDup* pi);

void NPilhas_inicializar(NPilhas* pi);
void NPilhas_deslocarDir(NPilhas* pi, int k);
void NPilhas_deslocarEsq(NPilhas* pi, int k);
int NPilhas_cheia(NPilhas* pi, int k);
int NPilhas_retornar(NPilhas* pi, int k);
void NPilhas_inserir(NPilhas* pi, int k, int ch);

// matriz esparsa

typedef struct {
    int Maxlinha;
    int Maxcoluna;
    NOMatrizEsp* ini;
} MatrizEsp;


typedef struct m {
    int linha;
    int coluna;
    int chave;
    struct m* prox;
} NOMatrizEsp;

// lista cruzada
typedef struct
{
    NOListaCr *lin[MAX];
    NOListaCr *col[MAX];
} ListaCr;

typedef struct m
{
    int l;
    int c;
    int chave;
    struct m *proxLin;
    struct m *proxCol;
} NOListaCr;



// LDS recursivamente