#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAXVER 100

// FILA EM FORMATO DE HEAP

typedef struct s {
    int heap[MAXVER];
    int heapSize;
} Heap;


void minHeapify(Heap *h, int i) {
    int l = 2 * i;
    int r = (2 * i) + 1;
    int min;
    if(l < h->heapSize && h->heap[l] < h->heap[i]) {
        min = l;
    }
    else min = i;
    if(l < h->heapSize && h->heap[r] < h->heap[i]) {
        min = r;
    }
    if(min != i) {
        int aux = h->heap[min];
        h->heap[min] = i;
        h->heap[i] = aux;
        minHeapify(h, min);
    }
}


void subirMin(Heap *h, int i) {
    while(i > 1 && h->heap[i] < h->heap[i/2]) {
        int aux = h->heap[i];
        h->heap[i] = h->heap[i/2];
        h->heap[i/2] = aux;
        i = i/2;
    }
}

void criarFila(Heap *h) {
    h->heapSize = MAXVER;
    for(int i = MAXVER / 2; i >= 1; i--) {
        minHeapify(h, i);
    }
}



int extrairFila(Heap* h) {
    if(h->heapSize < 1) return -1;
    int min = h->heap[1];
    h->heap[1] = h->heap[MAXVER - 1];
    h->heapSize--;
    minHeapify(h, 1);
    return min;
}


// FUNÇÕES ADICIONAIS PARA GRAFOS

void visitaProf(Grafo *g, int v, int *cor, int *desc, int *term, int *ant, int *tempo)
{
    cor[v] = 1; // deixa cinza
    desc[v] = ++(*tempo);
    for (ApontadorVertAdj u = primeiroListaAdj(g, v); u != ARESTA_NULA; u = proxListaAdj(g, v, u))
    {
        if (cor[idVertice(g, u)] == 0)
        {
            ant[idVertice(g, u)] = v;
            visitaProf(g, idVertice(g, u), cor, desc, term, ant, tempo);
        }
    }
    term[v] = ++(*tempo);
    cor[v] = 2;
}

bool grafoConexoND(Grafo *g)
{

    int *cor = (int *)malloc(sizeof(int) * g->numVer); // 0 = branco, 1 = cinza, 2 = preto
    int *desc = (int *)malloc(sizeof(int) * g->numVer);
    int *term = (int *)malloc(sizeof(int) * g->numVer);
    int *ant = (int *)malloc(sizeof(int) * g->numVer);
    int tempo = 0;

    for (int i = 0; i < g->numVer; i++)
    {
        cor[i] = desc[i] = term[i] = 0;
        ant[i] = -1;
    }

    visitaProf(g, 0, cor, desc, term, ant, &tempo);
    for (int i = 0; i < g->numVer; i++)
    {
        printf("vert: %d   cor: %d\n", i, cor[i]);   
        if (cor[i] != 2) {
            return false;
        }
    }
    return true;
}











/*





// Manutenção do Min-Heap (Sobe o menor)
void subir_min(int *heap, int i)
{
    while (i > 0 && heap[i] < heap[(i - 1) / 2])
    {
        int temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

// Manutenção do Min-Heap (Desce o maior/errado)
void descer_min(int *heap, int n, int i)
{
    int menor = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n && heap[esq] < heap[menor])
        menor = esq;
    if (dir < n && heap[dir] < heap[menor])
        menor = dir;

    if (menor != i)
    {
        int temp = heap[i];
        heap[i] = heap[menor];
        heap[menor] = temp;
        descer_min(heap, n, menor);
    }
}

// Operações da Fila
void inserir(int *heap, int *n, int valor)
{
    heap[*n] = valor;
    (*n)++;
    subir_min(heap, *n - 1);
}

int extrair_minimo(int *heap, int *n)
{

    int minimo = heap[0];
    heap[0] = heap[*n - 1];
    (*n)--;
    descer_min(heap, *n, 0);
    return minimo;
}

*/