#include <stdio.h>
#include "listas.h"





void LG_exibir(NOListaGen* p) {
    NOListaGen* atual = p;
    while(atual) {
        if(atual->tipo == 1) {
            printf("%d ", atual->chave);
        }
        else {
            LG_exibir(atual->subLista);
        }
        atual = atual->prox;
    }
}

void LG_exibirN(NOListaGen*p, int* n) {
    NOListaGen* atual = p;
    while(atual && *n > 0) {
        if(atual->tipo == 1) {
            printf("%d ", atual->chave);
            *n = *n - 1;
        }
        else {
            LG_exibirN(atual->subLista, n);
        }
        atual = atual->prox;
    }
}

bool LG_comparar(NOListaGen* p1, NOListaGen* p2) {
    if(!p1 && !p2) return true;
    if((p1 && !p2) || (!p1 && p2) || (p1->tipo != p2->tipo)) return false;
    if(p1->tipo == 1 && p1->chave != p2->chave) return false;
    if(p1->tipo == 2) {
        bool igual = LG_comparar(p1->subLista, p2->subLista);
        if(!igual) return false;
    }
    return LG_comparar(p1->prox, p2->prox);
}

NOListaGen* LG_duplicar(NOListaGen* p) {
    if(!p) return NULL;
    NOListaGen* novo = (NOListaGen*) malloc(sizeof(NOListaGen));
    novo->tipo = p->tipo;
    if(novo->tipo == 1) novo->chave = p->chave;
    else{
        novo->subLista = LG_duplicar(p->subLista);
    }
    novo->prox = LG_duplicar(p->prox);
    return novo;
}

