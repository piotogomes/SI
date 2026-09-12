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

// 6 verificar arvore enraizada

void enraizado(Vertice *g, int i, bool *resp)
{
    g[i].flag = 1;
    NO *p = g[i].inicio;
    while (p)
    {
        if (g[p->adj].flag == 1 && i != p->adj)
        {
            *resp = false;
        }
        if (g[p->adj].flag == 0)
        {
            enraizado(g, p->adj, resp);
        }
        p = p->prox;
    }
    g[i].flag = 2;
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

void exibirSuspeitos(Vertice *g, int id)
{
    for (int i = 1; i <= V; i++)
    {
        NO *p = g[i].inicio;
        while (p)
        {
            g[p->adj].visto = false;
            p = p->prox;
        }
    }
    for (int i = 1; i <= V; i++)
    {
        NO *p = g[i].inicio;
        while (p)
        {
            if (p->peso == id)
            {
                g[p->adj].visto = true;
            }
            p = p->prox;
        }
    }
    for (int i = 1; i <= 5; i++)
    {
        if (!g[i].visto)
            printf("%d\n", i);
    }
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
            g[p->adj].nPais = 0;
            p = p->prox;
        }
    }

    int chamadas[V + 1];

    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            chamadas[j] = 0;
        }
        NO *p = g[i].inicio;
        while (p)
        {
            if (chamadas[g[p->adj].pais] == 0)
            {
                chamadas[g[p->adj].pais]++;
                g[i].nPais++;
            }
            p = p->prox;
        }
    }
    int maior = 0;
    int maisChamada = 0;
    for (int i = 1; i <= 5; i++)
    {
        if (g[i].nPais > maior)
        {
            maior = g[i].nPais;
            maisChamada = i;
        }
    }
    return maisChamada;
}

// 12 e 13 grafo nao dirigido, ver ciclo e remover (fazer)

void removerCiclo(int g[V][V], int i, int pai, bool *resp, int flags[V])
{
    flags[i] = 1;
    for (int j = 1; j <= V; j++)
    {
        if (g[i][j] == 1)
        {
            if (flags[j] == 0)
            {
                removerCiclo(g, j, i, resp, flags);
            }
            if (flags[i] == 1 && j != pai)
            {
                *resp = false;
            }
        }
    }
    flags[i] = 2;
}

// 14 nao conexo quantos grupos

void prof14(Vertice *g, int i, int *count)
{
    g[i].flag = 1;
    NO *p = g[i].inicio;
    while (p)
    {
        if (g[p->adj].flag == 0)
        {
            prof14(g, p->adj, count);
        }
        p = p->prox;
    }
    g[i].flag = 2;
    (*count)++;
}

void prof15(Vertice *g, int i, NO **list)
{
    g[i].flag = 1;
    NO *p = g[i].inicio;
    while (p)
    {
        if (g[p->adj].flag == 0)
        {
            NO *novo = (NO *)malloc(sizeof(NO));
            novo->adj = p->adj;
            novo->prox = (*list);
            (*list) = novo;
            prof15(g, p->adj, list);
        }
        p = p->prox;
    }
    g[i].flag = 2;
}

NO *maiorGrupo(Vertice *g)
{
    int count = 0;
    int maior = 0;
    int inicioMaior;
    NO *lis = (NO *)malloc(sizeof(NO));
    for (int i = 1; i <= 6; i++)
    {
        if (g[i].flag == 0)
        {
            prof14(g, i, &count);
        }

        if (count > maior)
        {
            maior = count;
            inicioMaior = i;
        }
    }
    zerarFlag(g);
    lis->adj = inicioMaior;
    lis->prox = NULL;

    prof15(g, inicioMaior, &lis);
    return lis;
}

// 16 17 e 18, retornar caminho de a ate b

void prof16(Vertice *g, int a, int b, NO **lis, bool *achou)
{
    g[a].flag = 1;
    NO *p = g[a].inicio;
    while (p)
    {
        if (g[p->adj].flag == 0 && !(*achou))
        {
            NO *novo = (NO *)malloc(sizeof(NO));
            novo->adj = p->adj;
            novo->prox = (*lis);
            (*lis) = novo;
            prof16(g, p->adj, b, lis, achou);
        }
        if (p->adj == b)
        {
            *achou = true;
        }
        p = p->prox;
    }
    g[a].flag = 2;
}

void caminhoAateB(Vertice *g, int a, int b)
{
    bool achou = false;
    NO *list = (NO *)malloc(sizeof(NO));
    list->prox = NULL;
    list->adj = a;
    prof16(g, a, b, &list, &achou);
    if (achou)
    {
        while (list)
        {
            printf("%d\n", list->adj);
            list = list->prox;
        }
    }
}

// 19 grafo nao dir completeo

bool grafoCompleto(Vertice *g, int nV)
{
    for (int i = 1; i <= nV; i++)
    {
        NO *p = g[i].inicio;
        int count = 0;
        while (p)
        {
            count++;
            p = p->prox;
        }
        if (count + 1 != nV)
        {
            return false;
        }
    }
    return true;
}

// 20 complemento

Vertice *complemento(Vertice *g, int nV)
{
    Vertice *compG = (Vertice *)malloc(sizeof(Vertice) * (nV + 1));
    int adjs[nV + 1];
    for (int i = 1; i <= nV; i++)
    {
        compG[i].inicio = NULL;
        for (int j = 1; j <= nV; j++)
        {
            adjs[j] = 0;
        }
        adjs[i] = 1;
        NO *p = g[i].inicio;
        while (p)
        {
            adjs[p->adj] = 1;
            p = p->prox;
        }
        for (int k = 1; k <= nV; k++)
        {
            if (adjs[k] == 0)
            {
                NO *novo = (NO *)malloc(sizeof(NO));
                novo->adj = k;
                novo->prox = compG[i].inicio;
                compG[i].inicio = novo;
            }
        }
    }
    return compG;
}

// 21 e 22 e 23 sala mais proxima (tipo 1 = cheio, 0 = vazio)

NO *salaProx(Vertice *g, int i, int nV)
{
    Fila f;
    fila_inicializar(&f);
    fila_anexar(&f, i);
    zerarFlag(g);
    g[i].flag = 1;
    NO *resp = (NO *)malloc(sizeof(NO) * nV);
    resp = NULL;
    bool achou = false;
    while (!fila_vazia(&f))
    {
        i = fila_retornar(&f);
        g[i].flag = 2;
        NO *p = g[i].inicio;
        if (g[i].tipo == 0)
        {
            NO *novo = (NO *)malloc(sizeof(NO));
            novo->adj = i;
            novo->prox = resp;
            resp = novo;
            achou = true;
        }
        while (p)
        {
            if (g[p->adj].flag == 0 && !achou)
            {
                fila_anexar(&f, p->adj);
                g[p->adj].flag = 1;
            }
            p = p->prox;
        }
    }
    return resp;
}

// 24 usuarios com d graus de dist (na main inicializar as dist com -1)

void exibirAmigos(Vertice *g, int i, int d, int nV)
{
    Fila f;
    fila_inicializar(&f);
    zerarFlag(g);
    for (int j = 1; j <= nV; j++)
    {
        g[j].dist = -1;
    }
    g[i].flag = 1;
    g[i].dist = 0;
    fila_anexar(&f, i);
    while (!fila_vazia(&f))
    {

        i = fila_retornar(&f);
        if (g[i].dist <= d)
        {
            printf("grau: %d, amigo: %d\n", g[i].dist, i);
        }
        NO *p = g[i].inicio;
        g[i].flag = 2;
        while (p)
        {
            if (g[p->adj].flag == 0)
            {
                fila_anexar(&f, p->adj);
                g[p->adj].dist = g[i].dist + 1;
                g[p->adj].flag = 1;
            }
            p = p->prox;
        }
    }
}

int main()
{
    Vertice *g1 = (Vertice *)malloc(sizeof(Vertice) * (V + 1));

    inicializar(g1);
    insereAresta(g1, 1, 2, 0);
    insereAresta(g1, 1, 3, 0);
    insereAresta(g1, 3, 4, 0);
    insereAresta(g1, 3, 5, 0);
    insereAresta(g1, 5, 6, 0);
    insereAresta(g1, 5, 4, 0);

    exibirAmigos(g1, 1, 1, 6);
    return 0;
}