#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAXVER 100
typedef float Peso;

#define ARESTA_NULA -1
typedef int ApontadorVertAdj;
typedef struct
{

    Peso matriz[MAXVER][MAXVER];
    int numVer;

} Grafo;

#define VERT_INVAL -1

bool verificarVertice(Grafo *g, int v)
{
    if (!g)
        return false;
    if (v < 0 || v > g->numVer)
        return false;
    return true;
}

int idVertice(Grafo *g, ApontadorVertAdj v)
{
    return v;
}

bool inicializarGrafoAdj(Grafo *g, int numVer)
{
    g->numVer = numVer;
    if (!verificarVertice(g, numVer))
    {
        return false;
    }
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
    if (!verificarVertice(g, v1) || !verificarVertice(g, v2))
        return false;
    return g->matriz[v1][v2] != ARESTA_NULA;
}

Peso pesoAresta(Grafo *g, int v1, int v2)
{
    if (!existeAresta(g, v1, v2))
        return (Peso)-1;
    return g->matriz[v1][v2];
}

void insereAresta(Grafo *g, int v1, int v2, Peso p)
{
    if (!verificarVertice(g, v1) || !verificarVertice(g, v2))
        return;
    g->matriz[v1][v2] = p;
}

void insereArestaND(Grafo *g, int v1, int v2, Peso p)
{
    if (!verificarVertice(g, v1) || !verificarVertice(g, v2))
        return;
    g->matriz[v1][v2] = p;
    g->matriz[v2][v1] = p;
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
    if (!verificarVertice(g, v))
        return false;
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
    return proxListaAdj(g, v, -1);
}

void liberaGrafo(Grafo *g);

void imprimeGrafoND(Grafo *g)
// dot -Tpng grafo.dot -o imagem.png pra criar o png
{
    FILE *arq = fopen("grafo.dot", "w");
    fprintf(arq, "strict graph G { rankdir=LR; node [shape=rect, style=filled, color=lightblue];\n\n");

    for (int i = 0; i < g->numVer; i++)
    {
        for (int j = 0; j < g->numVer; j++)
        {
            if (g->matriz[i][j] != -1)
            {

                fprintf(arq, "%d -- %d [label="
                             "%.2f"
                             "];",
                        i, j, g->matriz[i][j]);
                fprintf(arq, "\n");
            }
        }
    }
    fprintf(arq, "}");
    fclose(arq);
}

void imprimeGrafoDir(Grafo *g)
// dot -Tpng grafo.dot -o imagem.png pra criar o png
{
    FILE *arq = fopen("grafo.dot", "w");
    fprintf(arq, "digraph G { rankdir=LR; node [shape=rect, style=filled, color=lightblue];\n\n");

    for (int i = 0; i < g->numVer; i++)
    {
        for (int j = 0; j < g->numVer; j++)
        {
            if (g->matriz[i][j] != -1)
            {

                fprintf(arq, "%d -> %d [label="
                             "%.2f"
                             "];",
                        i, j, g->matriz[i][j]);
                fprintf(arq, "\n");
            }
        }
    }
    fprintf(arq, "}");
    fclose(arq);
}
