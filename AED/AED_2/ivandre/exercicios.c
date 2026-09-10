// typedefs

#include "../../AED_1/listas.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "listaAdj.c"

// 1 e 2 escreva um algoritmo capaz de verificar laços e remover
// assumir grafo inicializado e resp == false

void verificarLaço(Vertice *g, int i, bool *resp, NO **ant)
{
    g[i].flag = 1;
    NO *p = g[i].inicio;
    while (p)
    {
        if (g[p->adj].flag == 1 && p->adj != i)
        {
            g[(**ant).adj].inicio = (*ant)->prox;
            *resp = true;
        }
        if (g[p->adj].flag == 0)
        {
            *ant = p;
            verificarLaço(g, p->adj, resp, ant);
        }
        p = p->prox;
    }
    g[i].flag = 2;
}

// 3 Algoritmo para destruir arestas

void destruirArestas(int m[V][V])
{
    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            m[i][j] == 0;
        }
    }
}

// 7 grafo não dirigido ponderado, retornar copia de g só com aresta com custo menor que c

Vertice *grafoMinCusto(Vertice *g, int c)
{
    Vertice *gr = (Vertice *)malloc(sizeof(Vertice) * (V + 1));
    inicializar(gr);
    for (int i = 1; i <= V; i++)
    {
        NO *p = g[i].inicio;
        while (p)
        {
            if (p->peso > c)
            {
                NO *novo = (NO *)malloc(sizeof(NO));
                novo->adj = p->adj;
                novo->prox = gr[i].inicio;
                gr[i].inicio = novo;
            }
            p = p->prox;
        }
    }
    return gr;
}

// 8 g1 em matriz e g2 em lista, verificar se g2 é subgrafo de g1

bool subgrafo(Vertice *g1, int g2[V][V])
{
    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            if (g2[i][j] == 1)
            {
                NO *p = g1[i].inicio;
                bool resp = false;
                while (p)
                {
                    if (p->adj == j)
                    {
                        resp = true;
                    }
                    p = p->prox;
                }
                if (!resp)
                {
                    return resp;
                }
            }
        }
    }
    return true;
}

// 9 g3 construido com as arestas de g1 que não estão em g2

Vertice *intersecGrafos(Vertice *g1, Vertice *g2)
{
    Vertice *g3 = (Vertice *)malloc(sizeof(Vertice) * (V + 1));
    inicializar(g3);
    for (int i = 1; i <= V; i++)
    {
        NO *p1 = g1[i].inicio;
        NO *p2 = g2[i].inicio;
        while (p1)
        {
            while (p2)
            {
                if (p1->adj == p2->adj)
                {
                    NO *novo = (NO *)malloc(sizeof(NO));
                    novo->adj = p1->adj;
                    novo->prox = g3[i].inicio;
                    g3[i].inicio = novo;
                }
                p2 = p2->prox;
            }
            p2 = g2[i].inicio;
            p1 = p1->prox;
        }
    }
    return g3;
}

// 10, emails

void exibirSuspeitos(Vertice *g, int i, int id)
{
    g[i].flag = 1;
    NO *p = g[i].inicio;
    while (p)
    {
        if (g[p->adj].flag == 0)
        {
            exibirSuspeitos(g, p->adj, id);
        }
        if (p->peso == id)
        {
            printf("não suspeito: %d", p->adj);
        }
        p = p->prox;
    }
    g[i].flag = 2;
}

// 11 chamadas, retornar o vertice que tenha maior numero de paises

int verticeMaisPaises(Vertice *g)
{
    // inicializar as contagens
    for (int i = 1; i <= V; i++)
    {
        NO *p = g[i].inicio;
        while (p)
        {
            g[p->adj].cont = 0;
            p = p->prox;
        }
    }

    for (int i = 1; i <= V; i++)
    {
        NO *p = g[i].inicio;
        while (p)
        {
            
        }
    }
}

int main()
{
    Vertice *g1 = (Vertice *)malloc(sizeof(Vertice) * (V + 1));

    inicializar(g1);
    insereAresta(g1, 1, 2, 2);
    insereAresta(g1, 2, 3, 20);
    insereAresta(g1, 3, 4, 25);
    insereAresta(g1, 4, 5, 26);
    insereAresta(g1, 5, 3, 23);

    Vertice *g3 = grafoMinCusto(g1, 24);

    for (int i = 1; i <= 5; i++)
    {
        NO *p = g3[i].inicio;
        while (p)
        {
            printf("%d -> %d", i, p->adj);
            p = p->prox;
        }
        printf("\n");
    }

    return 0;
}