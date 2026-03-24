#include <stdio.h>
#include <stdlib.h>

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
