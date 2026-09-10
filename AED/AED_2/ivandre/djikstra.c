#include "../../AED_1/listas.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define V 100

typedef struct s
{
    int adj;
    struct s *prox;
    int peso; // exemplo para achar o maniho com menor peso
} NO;

typedef struct
{
    NO *inicio;
    int flag;  // flags para a busca
    int via;   // para o algoritmo de retornar o trajeto do caminho mais curto
    int custo; // para guardar os custos de cada caminho

} Vertice;

// iniciar com flag zeradas e custos infinitos

void djikstra(Vertice *g, int i, int f)
{
    zerarFlag(g);
    g[i].flag = 1;
    for (int j = 1; j <= V; j++)
    {
        g[j].via = -1;
        g[j].custo = 1000000; // max int
    }
    g[i].custo = 0;
    while (true)
    {
        int z = -1;
        int custoz = 1000000;
        for (int j = 1; j <= V; j++)
        {
            if (g[j].flag == 0 && g[j].custo < custoz)
            {
                z = j;
                custoz = g[j].custo;
            }
        }
        if (z == -1)
        {
            return;
        }
        g[z].flag = 1;
        NO *p = g[z].inicio;
        while (p)
        {
            if (g[p->adj].flag == 0)
            {
                int temp = g[z].custo + p->peso;
                if (temp < g[p->adj].custo)
                {
                    g[p->adj].custo = temp;
                    g[p->adj].via = z;
                }
            }
            p = p->prox;
        }
    }
}