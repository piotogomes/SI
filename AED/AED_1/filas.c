#include <stdio.h>
#include "listas.h"

void fila_inicializar(Fila* f) {
    f->fim = NULL;
    f->inicio = NULL;
}

void fila_anexar(Fila* f, int ch) {
    NOfila* novo = (NOfila*) malloc(sizeof(NOfila));
    novo->chave = ch;
    novo->prox = NULL;
    if(f->fim) f->fim->prox = novo;
    else f->inicio = novo;
    f->fim = novo;
    return;
}

int fila_retornar(Fila* f) {
    if(f->inicio == NULL) return -1;
    int primeiro = f->inicio->chave;
    NOfila* aux = f->inicio;
    f->inicio = aux->prox;
    free(aux);
    if(f->inicio == NULL) f->fim == NULL;
    return primeiro;
}

bool fila_vazia(Fila* f) {
    return(f->inicio == NULL);
}

void filaEst_inicializar(FilaEst* f) {
    f->inicio = -1;
    f->fim = -1;
}

bool filaEst_anexar(FilaEst* f, int ch) {
    f->fim = (f->fim + 1) % MAX;
    f->A[f->fim].chave = ch;
    if(f->inicio == -1) f->inicio = f->fim;
    return true;
}
int filaEst_retornar(FilaEst* f) {
    if(f->inicio == -1) return -1;
    int aux =  f->A[f->inicio].chave;
    if(f->inicio == f->fim) {
        filaEst_inicializar(f);
    }
    f->inicio = (f->inicio + 1) % MAX;
    return aux;

}

void filaDu_anexar1(FilaDupla* f, int ch) {
    NOFilaDupla* novo = (NOFilaDupla*) malloc(sizeof(NOFilaDupla));
    novo->chave = ch;
    novo->ant = NULL;
    novo->prox = f->inicio1;
    if(f->inicio1 != NULL) f->inicio1->ant = novo;
    else {
        f->inicio2 = novo;
    } 
    f->inicio1 = novo;
    return;
}
void filaDu_anexar2(FilaDupla* f, int ch) {
    NOFilaDupla* novo = (NOFilaDupla*) malloc(sizeof(NOFilaDupla));
    novo->chave = ch;
    novo->prox = NULL;
    novo->ant = f->inicio2;
    if(f->inicio2 != NULL) f->inicio2->prox = novo;
    else {
        f->inicio2 = novo;
    } 
    f->inicio2 = novo;
    return;
}

int FilaDu_retornar2(FilaDupla* f) {
    if(f->inicio2 == NULL) return -1;
    int aux = f->inicio2->chave;
    NOFilaDupla* p = f->inicio2;
    f->inicio2 = f->inicio2->ant;
    free(p);
    if(f->inicio2 == NULL) {
        f->inicio1 = NULL;
    }
    else f->inicio2->prox = NULL;
}