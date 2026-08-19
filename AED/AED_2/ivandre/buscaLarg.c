#include "../../AED_1/listas.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define V 100

typedef struct s
{
    int adj;
    struct s *prox;
    int cia; // exemplo de usar sempre a mesma companhia nos voos (aresta)
} NO;

typedef struct
{
    NO *inicio;
    int flag;   // flags para a busca
    bool visto; // exemplo de viajar para cidades que contenham visto, e uma busca que retorna uma lista para poder viajar
    int cap;    // exemplo de achar as salas conectadas com capacidade >= x
    int tipo;   // 1 = posto (exemplo busca largura)
    int dist;   // para a busca em largura no exemplo de achar a distancia

} Vertice;

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
    for(int j = 1; j <= V; j++) {
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

int main()
{

    return 0;
}