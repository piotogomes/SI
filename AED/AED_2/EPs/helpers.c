#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXVER 100

// FILA EM FORMATO DE HEAP

typedef struct s
{
    int heap[MAXVER];
    int pos[MAXVER];
    int heapSize;
} Heap;

void trocar(Heap *h, int i, int j)
{
    int tempV = h->heap[i];
    h->heap[i] = h->heap[j];
    h->heap[j] = tempV;

    h->pos[h->heap[i]] = i;
    h->pos[h->heap[j]] = j;
}

void minHeapify(Heap *h, int i, Peso chPeso[])
{
    int l = 2 * i;
    int r = (2 * i) + 1;
    int min;
    if (l <= h->heapSize && chPeso[h->heap[l]] < chPeso[h->heap[i]])
    {
        min = l;
    }
    else
        min = i;
    if (r <= h->heapSize && chPeso[h->heap[r]] < chPeso[h->heap[min]])
    {
        min = r;
    }
    if (min != i)
    {
        trocar(h, i, min);
        minHeapify(h, min, chPeso);
    }
}

bool pertenceFila(Heap *h, int v)
{
    return h->pos[v] >= 1 && h->pos[v] <= h->heapSize;
}

void subirMin(Heap *h, int i, Peso chPeso[])
{

    while (i > 1 && chPeso[h->heap[i]] < chPeso[h->heap[i / 2]])
    {
        trocar(h, i, i / 2);
        i = i / 2;
    }
}

void criarFila(Heap *h, int numVer)
{
    h->heapSize = numVer;
    for (int i = 0; i < numVer; i++)
    {
        h->heap[i + 1] = i;
        h->pos[i] = i + 1;
    }
}

int posNaFila(Heap *h, int v)
{
    return h->pos[v];
}

int tamFila(Heap *h)
{
    return h->heapSize;
}

int extrairFila(Heap *h, Peso chPeso[])
{
    // if(h->heapSize < 1) return -1;
    int min = h->heap[1];
    h->pos[min] = -1;
    h->heap[1] = h->heap[h->heapSize];
    if (h->heapSize > 1)
    {
        h->pos[h->heap[1]] = 1;
    }
    h->heapSize--;
    minHeapify(h, 1, chPeso);
    return min;
}

// FUNÇÕES ADICIONAIS PARA GRAFOS

void visitaProfDistancia(Grafo *g, int v, int d, int *dist, int *cor, int *ant)
{

    cor[v] = 1; // deixa cinza
    dist[v] = d;
    for (ApontadorVertAdj u = primeiroListaAdj(g, v); u != ARESTA_NULA; u = proxListaAdj(g, v, u))
    {
        if (cor[idVertice(g, u)] == 0)
        {
            ant[idVertice(g, u)] = v;
            visitaProfDistancia(g, idVertice(g, u), d + pesoAresta(g, idVertice(g,u), v), dist, cor, ant);
        }
    }
    cor[v] = 2;
}

void visitaProfConexo(Grafo *g, int v, int *cor, int *ant)
{
    cor[v] = 1; // deixa cinza
    for (ApontadorVertAdj u = primeiroListaAdj(g, v); u != ARESTA_NULA; u = proxListaAdj(g, v, u))
    {
        if (cor[idVertice(g, u)] == 0)
        {
            ant[idVertice(g, u)] = v;
            visitaProfConexo(g, idVertice(g, u), cor, ant);
        }
    }
    cor[v] = 2;
}

bool grafoConexoND(Grafo *g)
{

    int *cor = (int *)malloc(sizeof(int) * g->numVer); // 0 = branco, 1 = cinza, 2 = preto
    int *ant = (int *)malloc(sizeof(int) * g->numVer);
    for (int i = 0; i < g->numVer; i++)
    {
        cor[i] = 0;
        ant[i] = -1;
    }

    visitaProfConexo(g, 0, cor, ant);
    for (int i = 0; i < g->numVer; i++)
    {
        if (cor[i] != 2)
        {
            return false;
        }
    }
    return true;
}

int verticeMaisLonge(Grafo *g)
{
    int *dist = (int *)malloc(sizeof(int) * g->numVer);
    int *cor = (int *)malloc(sizeof(int) * g->numVer); // 0 = branco, 1 = cinza, 2 = preto
    int *ant = (int *)malloc(sizeof(int) * g->numVer);
    visitaProfDistancia(g, 0, 0, dist, cor, ant);
    int v = 0;
    int maiorDist = -1;

    for (int i = 0; i < g->numVer; i++)
    {
        if (dist[i] > maiorDist)
        {
            maiorDist = dist[i];
            v = i;
        }
    }
    return v;
}
