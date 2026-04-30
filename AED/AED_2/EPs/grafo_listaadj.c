#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAXVER 100
typedef float Peso;

#define VERT_INVAL -1

#define ARESTA_NULA NULL
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
typedef Aresta *ApontadorVertAdj;

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
    return v->vadj;
}

bool inicializarGrafoAdj(Grafo *g, int numVer)
{
    g->numVer = numVer;
    if (!verificarVertice(g, numVer))
    {
        return false;
    }
    if (!(g->listaAdj = (ApontadorVertAdj *)calloc(numVer, sizeof(ApontadorVertAdj))))
        return false;
    return true;
}

bool existeAresta(Grafo *g, int v1, int v2)
{
    if (!verificarVertice(g, v1) || !verificarVertice(g, v2)){
        return false;
    }
    ApontadorVertAdj atual = g->listaAdj[v1];
    while (atual)
    {
        if (atual->vadj == v2)
        {
            return true;
        }
        atual = atual->prox;
    }

    return false;
}

Peso pesoAresta(Grafo *g, int v1, int v2)
{
    if (!existeAresta(g, v1, v2))
        return (Peso)-1;
    ApontadorVertAdj atual = g->listaAdj[v1];
    while (idVertice(g, atual) != v2)
    {
        atual = atual->prox;
    }
    return atual->p;
}

void insereAresta(Grafo *g, int v1, int v2, Peso p)
{
    if (!verificarVertice(g, v1) || !verificarVertice(g, v2))
        return;
    if (existeAresta(g, v1, v2))
        return;
    ApontadorVertAdj novo = (ApontadorVertAdj)malloc(sizeof(Aresta));
    if (!novo)
        return;
    novo->p = p;
    novo->vadj = v2;
    novo->prox = g->listaAdj[v1];
    g->listaAdj[v1] = novo;
}

void insereArestaND(Grafo *g, int v1, int v2, Peso p)
{
    if (!verificarVertice(g, v1) || !verificarVertice(g, v2))
        return;
    ApontadorVertAdj novo1 = (ApontadorVertAdj)malloc(sizeof(Aresta));
    if (!novo1)
        return;
    novo1->p = p;
    novo1->vadj = v2;
    novo1->prox = g->listaAdj[v1];
    g->listaAdj[v1] = novo1;

    ApontadorVertAdj novo2 = (ApontadorVertAdj)malloc(sizeof(Aresta));
    if (!novo2)
        return;
    novo2->p = p;
    novo2->vadj = v1;
    novo2->prox = g->listaAdj[v2];
    g->listaAdj[v2] = novo2;
}

bool removerAresta(Grafo *g, int v1, int v2, Peso *p)
{
    ApontadorVertAdj atual = g->listaAdj[v1];
    ApontadorVertAdj ant = NULL;
    while (idVertice(g, atual) != v2)
    {
        ant = atual;
        atual = atual->prox;
    }
    if (!atual)
    {
        return false;
    }
    if (ant)
        ant->prox = atual->prox;
    else
        g->listaAdj[v1] = atual->prox;
    *p = atual->p;
    free(atual);
    return true;
}

bool listaAdjVazia(Grafo *g, int v)
{
    if (!verificarVertice(g, v))
        return false;
    return (g->listaAdj[v] == NULL);
}

ApontadorVertAdj primeiroListaAdj(Grafo *g, int v)
{
    return g->listaAdj[v];
}

ApontadorVertAdj proxListaAdj(Grafo *g, int v, ApontadorVertAdj atual)
{
    if (!atual)
    {
        return ARESTA_NULA;
    }
    return (atual->prox);
}

void liberaGrafo(Grafo *g)
{
    for (int i = 0; i < g->numVer; i++)
    {
        ApontadorVertAdj atual = g->listaAdj[i];
        while (atual)
        {
            g->listaAdj[i] = atual->prox;
            atual->prox = NULL;
            free(atual);
            atual = g->listaAdj[i];
        }
    }

    free(g->listaAdj);
    g->listaAdj = NULL;
    g->numVer = 0;
}

// dot -Tpng grafo.dot -o imagem.png pra criar o png

void imprimeGrafoND(Grafo *g)
{

    ApontadorVertAdj atual;
    FILE *arq = fopen("grafo.dot", "w");
    fprintf(arq, "strict graph G { rankdir=LR; node [shape=rect, style=filled, color=lightblue];\n\n");

    for (int i = 0; i < g->numVer; i++)
    {
        atual = g->listaAdj[i];
        while (atual)
        {

            fprintf(arq, "%d -- %d [label="
                         "%.2f"
                         "];",
                    i, atual->vadj, atual->p);
            fprintf(arq, "\n");
            atual = atual->prox;
        }
    }
    fprintf(arq, "}");
    fclose(arq);
}

void imprimeGrafoDir(Grafo *g)
{

    ApontadorVertAdj atual;
    FILE *arq = fopen("grafo.dot", "w");
    fprintf(arq, "digraph G { rankdir=LR; node [shape=rect, style=filled, color=lightblue];\n\n");

    for (int i = 0; i < g->numVer; i++)
    {
        atual = g->listaAdj[i];
        while (atual)
        {

            fprintf(arq, "%d -> %d [label="
                         "%.2f"
                         "];",
                    i, atual->vadj, atual->p);
            fprintf(arq, "\n");
            atual = atual->prox;
        }
    }
    fprintf(arq, "}");
    fclose(arq);
}