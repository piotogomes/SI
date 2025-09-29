#include <stdbool.h>


#define MAX 1000

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

