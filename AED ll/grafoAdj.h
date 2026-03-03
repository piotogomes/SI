#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXVER 100
#define VERT_INVAL -1
#define ARESTA_NULA -1
typedef int Peso;

typedef struct
{

    Peso matriz[MAXVER][MAXVER];
    int numVer;

} Grafo;

void verificarVertice(Grafo* g, int v) {
    if(v < 0 || v > g->numVer) exit(-1);

}

bool inicializarGrafoAdj(Grafo *g, int numVer)
{
    verificarVertice(g, numVer);
    g->numVer = numVer;
    for (int i = 0; i < numVer; i++)
    {
        for (int j = 0; j < numVer; j++)
        {
            g->matriz[i][j] = ARESTA_NULA;
        }
    }
    return true;
}

bool existeAresta(Grafo* g, int v1, int v2) {
    verificarVertice(g, v1);
    verificarVertice(g, v2);
    return g->matriz[v1][v2] != ARESTA_NULA;
}

void insereAresta(Grafo* g, int v1, int v2, Peso p) {
    verificarVertice(g, v1);
    verificarVertice(g, v2);
    g->matriz[v1][v2] = p;

}

bool removerAresta(Grafo* g, int v1, int v2, Peso* p) {
    if(!existeAresta(g, v1, v2)) return false;
    *p = g->matriz[v1][v2];
    g->matriz[v1][v2] = ARESTA_NULA;
    return true;
}

bool listaAdjVazia(Grafo* g, int v) {
    verificarVertice(g, v);
    for(int i = 0; i < g->numVer; i++) {
        if(g->matriz[v][i] != ARESTA_NULA) return false;
    }
    return true;
}

int proxListaAdj(Grafo* g, int v, int atual) {
    for(int i = atual + 1; i < g->numVer; i++) {
        if(g->matriz[v][i] != ARESTA_NULA) return i;   
    }
    return VERT_INVAL;
}

void imprimeGrafo(Grafo* g) {
    for (int i = 0; i < g->numVer; i++) {
        for (int j = 0; j < g->numVer; j++) {
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}
    