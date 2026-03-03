#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXVER 100
#define VERT_INVAL -1
#define ARESTA_NULA NULL

typedef int Peso;

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
    if (!(g->listaAdj = (Aresta **)calloc(numVer, sizeof(Aresta*))))
        return false;
    return true;
}

bool existeAresta(Grafo *g, int v1, int v2)
{
    verificarVertice(g, v1);
    verificarVertice(g, v2);
    Aresta* atual = g->listaAdj[v1]->prox;
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
    Aresta* novo = (Aresta*) malloc(sizeof(Aresta));
    novo->p = p;
    novo->prox = NULL;
    novo->vadj = v2;
    g->listaAdj[v1]->prox = novo;

}

bool removerAresta(Grafo *g, int v1, int v2, Peso *p)
{
    if (!existeAresta(g, v1, v2))
        return false;
    Aresta* atual = g->listaAdj[v1];
    Aresta* ant = NULL;
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
    return (g->listaAdj[v]->prox);
}

int proxListaAdj(Grafo *g, int v, int atual)
{
    for (int i = atual + 1; i < g->numVer; i++)
    {
        if (g->matriz[v][i] != ARESTA_NULA)
            return i;
    }
    return VERT_INVAL;
}

void imprimeGrafo(Grafo *g)
{
    for (int i = 0; i < g->numVer; i++)
    {
        for (int j = 0; j < g->numVer; j++)
        {
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}
