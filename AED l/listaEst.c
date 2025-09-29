#include <stdio.h>
#include <stdbool.h>
#include "listas.h"

#define MAX 1000


void lle_inicializar(ListaLigEst* l) {
    l->inicio = -1;
    l->dispo = 0;
    for(int i = 0; i < MAX - 1; i++) {
        l->A[i].prox = i+1;
    }
    l->A[MAX - 1].prox = -1;
}

void lle_exibir(ListaLigEst *l) {

    for(int i = l->inicio; i != -1; i = l->A[i].prox) {
        printf("%d ", l->A[i].chave);
        printf("i: %d, prox: %d\n", i, l->A[i].prox);
    }
    printf("\n");
}

int lle_busca_f(ListaLigEst *l, int ch, int* ant) {
    *ant = -1;
    for(int i = l->inicio; i != -1; i = l->A[i].prox) {
        if(l->A[i].chave > ch) break;
        if(l->A[i].chave == ch) return i;
        *ant = i;


    }
    return -1;
}

int lle_busca(ListaLigEst *l, int ch) {
    int ant;
    return lle_busca_f(l, ch, &ant);
}


void lle_liberarDispo(ListaLigEst* l, int j){
    l->A[j].prox = l->dispo;
    l->dispo = j;
}

bool lle_excluir(ListaLigEst *l, int ch) {
    int ant;
    int i = lle_busca_f(l, ch, &ant);
    if(i == -1) return false;
    if(ant != -1) {
        l->A[ant].prox = l->A[i].prox;
    }
    else {
        l->inicio = l->A[i].prox;
    }
    lle_liberarDispo(l, i);
    return true;
}

int lle_obterDispo(ListaLigEst* l) {
    int aux = l->dispo;
    printf("prox dispo %d\n", l->A[l->dispo].prox);
    if(aux != -1) l->dispo = l->A[l->dispo].prox;
    return aux;

}

bool lle_inserir(ListaLigEst* l, int ch) {
    int ant;
    int atual = lle_busca_f(l, ch, &ant);
    int novo = lle_obterDispo(l);
    if(novo == -1) return false; // atual != -1 significa duplicate
    l->A[novo].chave = ch;
    if(ant != -1) {
        l->A[novo].prox = l->A[ant].prox;
        l->A[ant].prox = novo;
    }
    else {
        l->A[novo].prox = l->inicio;
        l->inicio = novo;
    }
    return true;
}

bool lle_trocarPosProx(ListaLigEst* l, int ch) {
    int ant, aux;
    int i = lle_busca_f(l, ch, &ant);
    if(i == -1 || l->A[i].prox == -1) return false;
    aux = l->A[l->A[i].prox].prox;
    if(ant == -1) {
        l->A[l->A[i].prox].prox = i;
        l->inicio = l->A[i].prox;
        l->A[i].prox = aux;
        return true;
    }

    l->A[l->A[i].prox].prox = l->A[ant].prox;
    l->A[ant].prox = l->A[i].prox;
    l->A[i].prox = aux;
    return true;
}

bool lle_verificarListaLigEstIguais(ListaLigEst* l1, ListaLigEst* l2) {
    if(l2->inicio == -1 && l1->inicio == -1) return true;
    if((l2->inicio == -1) != (l1->inicio == -1)) return false;
    for(int i = l1->inicio, j = l2->inicio; (i != -1 && j != -1); i = l1->A[i].prox, j = l2->A[j].prox) {
        if ((l1->A[i].prox == -1) != (l2->A[j].prox == -1)) return false; // fim da l1 mas não fim da l2 ou fim da l2 mas não fim da l1
        if(l1->A[i].chave != l2->A[j].chave) return false;
    }
    return true;
}

bool verificarLleIgualLs(ListaLigEst* l1, ListaSeq* l2) {
    if(l2->tam == 0 && l1->inicio == -1) return true;
    if((l2->tam == 0) != (l1->inicio == -1)) return false;
    int j = l1->inicio;
    for(int i = 0; i < l2->tam; i++) {
        if(j == -1) return false;
        if((l1->A[j].chave != l2->A[i].chave)) return false;
        j = l1->A[j].prox;
    }
    return (j != -1) ? false : true;
}

bool lle_excluirDupes(ListaLigEst* l, int ch) {
    int ant;
    int i = lle_busca_f(l, ch, &ant);
    if(i == -1) return false;
    // l->dispo = l->A[ant].prox;
    while(ch == l->A[l->A[ant].prox].chave && i != -1) {
        l->A[ant].prox = l->A[i].prox;
        // lle_excluir(l, ch);
        i = l->A[i].prox;
        

    }


    return true;
}