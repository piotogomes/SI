#include "grafoAPI.h"


void visitaProf(Grafo* g, int i, int* cor, int* desc, int* term, int* ant, int* tempo) {
    cor[i] = 1; // deixa cinza
    desc[i] = ++(*tempo);
    ApontadorVertAdj vert = primeiroListaAdj(g, i);
    while(vert != ARESTA_NULA) {
        if(cor[vert] == 0) { // colocar retorna vert
            ant[i] = vert;
            visitaProf(g, vert, cor, desc, term, ant, &tempo);
        }
        vert = proxListaAdj(g, i, vert);
    }
    term[i] = ++(*tempo);
    cor[i] = 2;
}

void buscaProfundidade(Grafo* g) {
    //malloc dos vetores cor, descoberta, termino e anterior
    int* cor = (int*) malloc(sizeof(int)*g->numVer); // 0 = branco, 1 = cinza, 2 = preto
    int* desc = (int*) malloc(sizeof(int)*g->numVer);
    int* term = (int*) malloc(sizeof(int)*g->numVer);
    int* ant = (int*) malloc(sizeof(int)*g->numVer);
    int tempo = 0;

    for(int i = 0; i < g->numVer; i++) {
        cor[i] = desc[i] = term[i] = 0;
        ant[i] = -1;
    }

    for(int i = 0; i < g->numVer; i++) {
        if(cor[i] == 0) {
            visitaProf(g, i, cor, desc, term, ant, &tempo);
        }
    }

}



int main() {

    Grafo g;
    inicializarGrafoAdj(&g, 10);
    imprimeGrafo(&g);


    return 0;
}

