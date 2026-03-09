#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXVER 100
#define VERT_INVAL -1
#define ARESTA_NULA NULL

typedef int Peso;
typedef Aresta* ApontadorVertAdj;

typedef struct str
{
    int vadj;
    Peso p; 
    struct str *prox;
} Aresta;

typedef struct
{
    Aresta **listaAdj;
    int numVer;
} Grafo;

void verificarVertice(Grafo *g, int v)
{
    if (!g)
        exit(-1);
    if (v < 0 || v > g->numVer)
        exit(-1);
}

bool inicializarGrafoAdj(int numVer, Grafo *g)
{
    verificarVertice(g, numVer);
    g->numVer = numVer;
    if (!(g->listaAdj = (Aresta **)calloc(numVer, sizeof(ApontadorVertAdj))))
        return false;
    return true;
}

bool existeAresta(Grafo *g, int v1, int v2)
{
    verificarVertice(g, v1);
    verificarVertice(g, v2);
    ApontadorVertAdj atual = g->listaAdj[v1];
    while(atual) {
        if (atual->vadj == v2) {
            return true;
        }
        atual = atual->prox;
    }

    return ARESTA_NULA;
}

void insereAresta(Grafo *g, int v1, int v2, Peso p)
{
    verificarVertice(g, v1);
    verificarVertice(g, v2);
    ApontadorVertAdj novo = (ApontadorVertAdj) malloc(sizeof(Aresta));
    novo->p = p;
    novo->prox = NULL;
    novo->vadj = v2;
    g->listaAdj[v1]->prox = novo;

}

bool removerAresta(Grafo *g, int v1, int v2, Peso *p)
{
    if (!existeAresta(g, v1, v2))
        return false;
    ApontadorVertAdj atual = g->listaAdj[v1];
    ApontadorVertAdj ant = NULL;
    while(atual) {
        if (atual->vadj == v2) {
            ant->prox = atual->prox;
            *p = atual->p;
            free(atual);
            return true;
        }
        ant = atual;
        atual = atual->prox;
    }
    return false;
}

bool listaAdjVazia(Grafo *g, int v)
{
    verificarVertice(g, v);
    return (g->listaAdj[v] == NULL);
}

ApontadorVertAdj primeiroListaAdj(Grafo* g, int v) {
    verificarVertice(g, v);
    return g->listaAdj[v];
}


ApontadorVertAdj proxListaAdj(Grafo *g, int v, ApontadorVertAdj atual)
{
    if (!atual) {
        return ARESTA_NULA;
    }
        return (atual->prox);
}   

void imprimeGrafo(Grafo *g)
{
    ApontadorVertAdj atual;
    for (int i = 0; i < g->numVer; i++)
    {
        atual = g->listaAdj[i];
        if(!atual) {
            printf("Vertice %d sem adj\n", i);
            continue;
        }
        printf("Adj's do %d (Peso,Vert): ", i);
        while(atual) {
            printf("(%d, %d) ", atual->p, atual->vadj);
            atual = atual->prox;
        }
        printf("\n");
    }
}
