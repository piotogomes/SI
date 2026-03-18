#include "grafoAPI.h"

#define VERT_INVAL -1

void verificarVertice(Grafo *g, int v)
{
    if (v < 0 || v > g->numVer)
        exit(-1);
}

int idVertice(Grafo *g, ApontadorVertAdj v)
{
    return v;
}

bool inicializarGrafoAdj(Grafo *g, int numVer)
{
    g->numVer = numVer;
    verificarVertice(g, numVer);
    for (int i = 0; i < numVer; i++)
    {
        for (int j = 0; j < numVer; j++)
        {
            g->matriz[i][j] = ARESTA_NULA;
        }
    }
    return true;
}

bool existeAresta(Grafo *g, int v1, int v2)
{
    verificarVertice(g, v1);
    verificarVertice(g, v2);
    return g->matriz[v1][v2] != ARESTA_NULA;
}

void insereAresta(Grafo *g, int v1, int v2, Peso p)
{       
    verificarVertice(g, v1);
    verificarVertice(g, v2);
    g->matriz[v1][v2] = p;
}

bool removerAresta(Grafo *g, int v1, int v2, Peso *p)
{
    if (!existeAresta(g, v1, v2))
        return false;
    *p = g->matriz[v1][v2];
    g->matriz[v1][v2] = ARESTA_NULA;
    return true;
}

bool listaAdjVazia(Grafo *g, int v)
{
    verificarVertice(g, v);
    for (int i = 0; i < g->numVer; i++)
    {
        if (g->matriz[v][i] != ARESTA_NULA)
            return false;
    }
    return true;
}
ApontadorVertAdj proxListaAdj(Grafo *g, int v, ApontadorVertAdj atual)
{
    for (int i = atual + 1; i < g->numVer; i++)
    {
        if (g->matriz[v][i] != ARESTA_NULA)
            return i;
    }

    return VERT_INVAL;
}

ApontadorVertAdj primeiroListaAdj(Grafo *g, int v)
{
    verificarVertice(g, v);
    return proxListaAdj(g, v, -1);
}

void liberaGrafo(Grafo *g);

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

bool existeCaminho(Grafo *g, int v1, int v2);
