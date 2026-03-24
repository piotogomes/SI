#include <stdio.h>
#include "listas.h"



// percurso em nivel (fila em elementos de arvore bin)


void ArBin_percursoNv(NOArvoreBIN* raiz){
    Fila* f;
    f->inicio = NULL;
    fila_anexar(f, raiz);
    while(f->inicio) {
        NOArvoreBIN* p = fila_retornar(f);
        printf("%d ", p->chave);
        if(p->esq) fila_anexar(f, p->esq);
        if(p->dir) fila_anexar(f, p->dir);
    }
}