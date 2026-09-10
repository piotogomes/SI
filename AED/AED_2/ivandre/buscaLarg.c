#include "../../AED_1/listas.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "listaAdj.c"



////////////////////////////////////////////////////////////////////////
//  CAMINHO MAIS CURTO
////////////////////////////////////////////////////////////////////////

// Busca em Largura

void larg(Vertice *g, int i)
{
    zerarFlag(g);
    g[i].flag = 1;
    Fila *f;
    fila_inicializar(f);
    fila_anexar(f, i);
    while (!fila_vazia)
    {
        i = fila_retornar(f);
        g[i].flag = 2;
        NO *p = g[i].inicio;
        while (p)
        {
            if (g[p->adj].flag == 0)
            {
                fila_anexar(f, p->adj);
                g[p->adj].flag = 1;
            }
            p = p->prox;
        }
    }
}

// em matriz

void largM(int m[V][V], int i, int flags[V])
{
    Fila *f;
    fila_inicializar(f);
    flags[i] = 1;
    fila_anexar(f, i);
    while (!fila_vazia)
    {
        i = fila_retornar(f);
        flags[i] == 2;
        for (int j = 1; j <= V; j++)
        {
            if (m[i][j] == 1 && flags[j] == 0)
            {
                fila_anexar(f, j);
                flags[j] == 1;
            }
        }
    }
}

// exemplo imprime vertice mais perto a partir da quantidade de vertices e sua distancia

void verticeMaisPerto(Vertice *g, int i, int tipo)
{
    zerarFlag(g);
    g[i].flag = 1;
    for (int j = 1; j <= V; j++)
    {
        g[j].dist = -1;
    }
    g[i].dist = 0;
    Fila *f;
    fila_inicializar(f);
    fila_anexar(f, i);
    while (!fila_vazia)
    {
        i = fila_retornar(f);
        g[i].flag = 2;
        if (g[i].tipo == tipo)
        {
            printf("%d com dist %d", i, g[i].dist);
            while (!fila_vazia)
            {
                fila_retornar(f);
            }
            return;
        }
        NO *p = g[i].inicio;
        while (p)
        {
            if (g[p->adj].flag == 0)
            {
                g[p->adj].dist = g[i].dist + 1;
                fila_anexar(f, p->adj);
                g[p->adj].flag = 1;
            }
            p = p->prox;
        }
    }
}

// achar todos os caminho a partir das vias e atualiza os custos, mas não pega o menor custo

void caminhos(Vertice *g, int i, int f)
{
    zerarFlag(g);
    g[i].flag = 1;
    for (int j = 1; j <= V; j++)
    {
        g[j].via = -1;
        // g[j].peso = INT_MAX
    }
    g[i].custo = 0;
    Fila *f;
    fila_anexar(f, i);
    while (!fila_vazia)
    {
        i = fila_retornar(f);
        NO *p = g[i].inicio;
        while (p)
        {
            if (g[p->adj].flag == 0)
            {
                g[p->adj].flag = 1;
                fila_anexar(f, p->adj);
                g[p->adj].via = i;
                g[p->adj].custo = g[i].custo + p->peso;
            }
            p = p->prox;
        }
        g[i].flag = 2;
    }
    int k = g[f].via;
    while (k != -1)
    {
        printf("%d\n", k);
        k = g[k].via;
    }
}

// djikstra caminho de custo minimo



int main()
{

    return 0;
}