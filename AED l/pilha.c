#include <stdio.h>
#include "listas.h"

void pilha_inicializar(Pilha* pi) {
    pi->topo = NULL;
}
void pilha_inserir(Pilha* pi, int ch) {
    NOpilha* novo = (NOpilha*) malloc(sizeof(NOpilha));
    novo->chave = ch;
    novo->prox = pi->topo;
    pi->topo = novo;
}
int pilha_retornar(Pilha* pi) {
    if(pi->topo == NULL) return -1;
    int ch = pi->topo->chave;
    Pilha* aux = pi->topo;
    pi->topo = pi->topo->prox;
    free(aux);
    return ch;
}

void pilhaEst_inicializar(PilhaEst* pi) {
    pi->topo = -1;
}
void pilhaEst_inserir(PilhaEst* pi, int ch) {
    if(pi->topo == MAX - 1) return;
    pi->topo++;
    pi->A[pi->topo].chave = ch;
    return;
}
int pilhaEst_retornar(PilhaEst* pi){
    if(pi->topo == -1) return -1;
    int aux = pi->A[pi->topo].chave;
    pi->topo--;
    return aux;
}

void pilhaDup_inicializar(PilhaDup* pi) {
    pi->topo1 = -1;
    pi->topo2 = MAX;    if(pi->topo2 == MAX) return -1;
    int aux = pi->A[pi->topo2].chave;
    pi->topo2++;
    return aux;
}

void pilhaDup_inserir1(PilhaDup* pi, int ch){
    if(pi->topo1 + 1 == pi->topo2) return;
    pi->topo1++;
    pi->A[pi->topo1].chave = ch;
    return;

}
int pilhaDup_retornar1(PilhaDup* pi){
    if(pi->topo1 == -1) return -1;
    int aux = pi->A[pi->topo1].chave;
    pi->topo1--;
    return aux;
}

void pilhaDup_inserir2(PilhaDup* pi, int ch) {
    if(pi->topo1 + 1 == pi->topo2) return;
    pi->topo2--;
    pi->A[pi->topo2].chave = ch;
    return;
}
int pilhaDup_retornar2(PilhaDup* pi) {
    if(pi->topo2 == MAX) return -1;
    int aux = pi->A[pi->topo2].chave;
    pi->topo2++;
    return aux;
}

void NPilhas_inicializar(NPilhas* pi) {
    for(int i = 0; i <= NP; i++) {
        pi->base[i] = (i*(MAX/NP)) - 1;
        pi->topo[i] = pi->base[i];
    }
}

int NPilhas_cheia(NPilhas* pi, int k) {
    if(pi->topo[k] == pi->base[k+1]) return 1;
    return 0;
}

void NPilhas_deslocarDir(NPilhas* pi, int k){
    if(!NPilhas_cheia(pi, k) || k < 1 || k >= NP) return; 
    for(int i = pi->topo[k]; i > pi->base[k]; i--) {
        pi->A[i+1] = pi->A[i];
    }
    pi->base[k]++;
    pi->topo[k]++;
}
void NPilhas_deslocarEsq(NPilhas* pi, int k){
    if(!NPilhas_cheia(pi, k) || k < 1 || k >= NP) return; 
    for(int i = pi->base[k]; i <= pi->topo[k]; i++) {
        pi->A[i-1] = pi->A[i];
    }
    pi->base[k]--;
    pi->topo[k]--;
}

int NPilhas_retornar(NPilhas* pi, int k){
    if(k < 0 || k >= NP || pi->base[k] == pi->topo[k]) return -1;
    pi->topo[k]--;
    return pi->A[pi->topo[k] + 1].chave;
}

void NPilhas_inserir(NPilhas* pi, int k, int ch) {
    if(k < 0 || k >= NP) return;
    if(Pilhas_cheia(pi, k)) {
        for(int i = NP - 1; i > k; i--) {
            NPilhas_deslocarDir(pi, i);
        }
    }
    if(Pilhas_cheia(pi, k)) {
        for(int i = 1; i <= k; i++) {
            NPilhas_deslocarEsq(pi, i);
        }
    }
    if(!NPilhas_cheia(pi, k)) {
        pi->topo[k]++;
        pi->A[pi->topo[k]].chave = ch;
    }
}