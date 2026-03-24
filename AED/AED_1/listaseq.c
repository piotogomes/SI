#include <stdio.h>
#include <stdbool.h>
#include "listas.h"



void ls_inicializar(ListaSeq* l) {
    l->tam = 0;
}
void ls_exibir(ListaSeq* l) {

    for(int i = 0; i < l->tam; i++) {
        printf("%d ", l->A[i].chave);
    }
    printf("\n");

}
int ls_buscaBin(ListaSeq* l, int ch) {
    int meio = l->tam / 2;
    int ini = 0;
    int fim = l->tam - 1;
    while(ini <= fim) {
        if(l->A[meio].chave < ch) {
            ini = meio + 1;
        }
        else if(l->A[meio].chave > ch) {
            fim = meio - 1;
        }
        else return meio;
        meio = (ini + fim) / 2;
    }
    return -1;
}
bool ls_excluir(ListaSeq* l, int ch) {
    int pos = ls_buscaBin(l, ch);
    if(pos == -1) return false;
    for(int i = pos; i < l->tam - 1; i++) {
        l->A[i].chave = l->A[i+1].chave; 
    }
    l->tam--;
    return true;
}
bool ls_inserir(ListaSeq* l, int ch) {
    int pos = ls_buscaBin(l, ch);
    if(pos != -1 || l->tam == MAX) return false;
    if(l->tam == 0) {
        l->A[0].chave = ch;
        l->tam++;
        return true;
    }
    int i = l->tam - 1;
    while(l->A[i].chave > ch && i >= 0) {
        l->A[i+1].chave = l->A[i].chave;
        i--;
    }
    if (i < 0) l->A[0].chave = ch;
    else l->A[i+1].chave = ch;
    l->tam++;
    return true;
}
