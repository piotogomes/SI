#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "listas.h"


void llds_inicializar(ListaLDS* l) {
    l->inicio = NULL;
}
void llds_exibir(ListaLDS* l) {
    NOSim* atual = l->inicio;
    printf("Lista: ");
    if (atual == NULL) {
        return;
    }
    while(atual->prox != NULL){
        printf("%d ", atual->chave);
        atual = atual->prox;
    }
    printf("%d ", atual->chave);
    printf("\n");
    
}
NOSim* llds_busca(ListaLDS *l, int ch, NOSim** ant) {
    *ant = NULL;
    NOSim* atual = l->inicio;
    if (atual == NULL) {
        return NULL;
    }
    while(atual != NULL){

        if(atual->chave == ch) {
            return atual;
        }
        if(atual->chave > ch) {
            return NULL;
        }
        *ant = atual;
        atual = atual->prox;
    }

}
bool llds_excluir(ListaLDS *l, int ch) {
    NOSim* ant;
    NOSim* atual = llds_busca(l, ch, &ant);
    if(atual == NULL) {
        printf("Não há o elemento");
        return false;
    }
    if(atual == l->inicio) {
        l->inicio = atual->prox;
        free(atual);
        return true;
    }
    ant->prox = atual->prox;
    free(atual);
    return true;


}
bool llds_inserir(ListaLDS* l, int ch) {
    NOSim* ant;
    NOSim* atual = llds_busca(l, ch, &ant);
    if(atual) {
        printf("repetido\n");
        return false;
    }
    NOSim* novo = (NOSim*) malloc(sizeof(NOSim));
    novo->chave = ch;
    if(l->inicio == NULL) {
        l->inicio = novo;
        novo->prox = NULL;
        return true;
    }
    if(ant == NULL) {
        novo->prox = l->inicio;
        l->inicio = novo;
        return true;
    }
    novo->prox = ant->prox;
    ant->prox = novo;
    return true;

}

void llds_exibirRECU(NOSim* p) {
    if(p) printf("%d ", p->chave);
    llds_exibirRECU(p->prox);
    return;
}

void llds_inverterRECU(NOSim* p, NOSim* ant, NOSim** ini) {
    if(p) {
        llds_inverterRECU(p->prox, p, ini);
        p->prox = ant;
    }
    else *ini = ant;
}