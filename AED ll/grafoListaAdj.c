#include "grafoAPI.h"

#define VERT_INVAL -1




void verificarVertice(Grafo *g, int v)
{
    if (!g)
        exit(-1);
    if (v < 0 || v > g->numVer)
        exit(-1);
}

bool inicializarGrafoAdj(Grafo *g, int numVer)
{
    g->numVer = numVer;
    verificarVertice(g, numVer);
    if (!(g->listaAdj = (ApontadorVertAdj*) calloc(numVer, sizeof(ApontadorVertAdj))))
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
    if(!novo) return;
    novo->p = p;
    novo->vadj = v2;
    novo->prox = g->listaAdj[v1];
    g->listaAdj[v1] = novo;

}

bool removerAresta(Grafo *g, int v1, int v2, Peso *p)
{
    ApontadorVertAdj atual = g->listaAdj[v1];
    ApontadorVertAdj ant = NULL;
    while(atual) {
        ant = atual;
        atual = atual->prox;
    }
    if (!atual) {
        return false;
    }
    if(ant) ant->prox = atual->prox;
    else g->listaAdj[v1] = atual->prox;
    *p = atual->p;
    free(atual);
    return true;
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

void liberaGrafo(Grafo* g) {
    for(int i = 0; i < g->numVer; i++) {
        ApontadorVertAdj atual = g->listaAdj[i];
        while(atual) {
            g->listaAdj[i] = atual->prox;
            atual->prox = NULL; // apagar o ponteiro pra ninguem hackear o.o
            free(atual);
            atual = g->listaAdj[i];
        }
    }

    free(g->listaAdj);
    g->listaAdj = NULL; // apagar o ponteiro pra ninguem hackear o.o
    g->numVer = 0;
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
