#include <stdio.h>
#include "listas.h"


NOMatrizEsp* BuscaME(int i, int j, NOMatrizEsp** ant, MatrizEsp* matriz) {
    *ant = NULL;
    NOMatrizEsp* p = matriz->ini;
    while(p) {
        if(p->linha == i && p->coluna == j) {
            return p;
        }
        if((p->linha > i) || ((p->linha == i) && (p->coluna > j))) return NULL;
        *ant = p;
        p = p->prox;
    }
    return NULL;
}

void inserirME(int i, int j, int ch, MatrizEsp* matriz) {
    NOMatrizEsp* ant;
    NOMatrizEsp* atual = BuscaME(i, j, &ant, matriz);
    if(atual == NULL && ch == 0) return;
    if(atual && ch != 0) {
        atual->chave = ch;
        return;
    }
    if(atual && ch == 0) {
        if(ant) ant->prox = atual->prox;
        else matriz->ini = atual->prox;
        free(atual);
        return;
    }
    if(atual == NULL && ch != 0) {
        NOMatrizEsp* novo = (NOMatrizEsp*) malloc(sizeof(NOMatrizEsp));
        novo->chave = ch;
        novo->linha = i;
        novo->coluna = j;
        if(ant) {
            novo->prox = ant->prox;
        }
        else {
            novo->prox = matriz->ini;
            matriz->ini = novo;
        }

    }
}

// Dada uma coluna, retornar a soma dos elementos

int somarColuna(int j, MatrizEsp* matriz) {
    int soma = 0;
    NOMatrizEsp* p = matriz->ini;
    while(p) {
        if(p->coluna == j) {
            soma += p->chave;
        }
        p = p->prox;
    }
    return soma;
}

// Verificar se duas linha são identicas

int LinhasIdenticas(int l1, int l2, MatrizEsp* matriz) {
    NOMatrizEsp* ant; 
    NOMatrizEsp* inicioL1 = matriz->ini;
    NOMatrizEsp* inicioL2 = matriz->ini;
    while(inicioL1->linha) {
        if(inicioL1->linha == l1) break;
        if(inicioL1->linha > l1) {
            inicioL1 == NULL;
            break;
        }
        inicioL1 = inicioL1->prox;
    }
    while(inicioL2->linha) {
        if(inicioL2->linha == l2) break;
        if(inicioL2->linha > l2) {
            inicioL2 == NULL;
            break;
        }
        inicioL2 = inicioL2->prox;
    }
    NOMatrizEsp* p1 = inicioL1;
    NOMatrizEsp* p2 = inicioL2;
    while(p1 && p2) {
        if((p1->chave != p2->chave) || p1->coluna != p2->coluna) return 0;
        p1 = p1->prox;
        p2 = p2->prox;
        if(p1->linha != l1 || !p1){
            if(p2->linha != l2 || !p2){
                return 1;
            }
            else return 0;
        }
        if(p2->linha != l2 || !p2){
            if(p1->linha != l1 || !p1){
                return 1;
            }
            else return 0;
        }        
    }
    if(!p1 && !p2) return 1;
    return 0;
}