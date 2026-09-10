#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define V 100

typedef struct sr
{
    int adj;
    struct sr *prox;
    int cia;  // exemplo de usar sempre a mesma companhia nos voos (aresta)
    int peso; // exemplo para achar o maniho com menor peso
} NO;

typedef struct
{
    NO *inicio;
    int flag;   // flags para a busca
    bool visto; // exemplo de viajar para cidades que contenham visto, e uma busca que retorna uma lista para poder viajar
    int cap;    // exemplo de achar as salas conectadas com capacidade >= x
    int tipo;   // 1 = posto (exemplo busca largura)
    int dist;   // para a busca em largura no exemplo de achar a distancia
    int via;    // para o algoritmo de retornar o trajeto do caminho mais curto
    int custo;  // para guardar os custos de cada caminho
    int pais; // exercicio 11
    int cont; // contagem de paises ex 11

} Vertice;

void inicializar(Vertice *g)
{
    for (int i = 1; i <= V; i++)
    {
        g[i].inicio = NULL;
        g[i].flag = 0; // para a busca, 0 = n descoberto, 1 = descoberto, 2 = concluido
    }
}

void zerarFlag(Vertice *g)
{
    for (int i = 1; i <= V; i++)
    {
        g[i].flag = 0; // para a busca, 0 = n descoberto, 1 = descoberto, 2 = concluido
    }
}

bool existeAresta(Vertice *g, int v1, int v2, NO **ant)

{
    *ant = NULL;
    NO *p = g[v1].inicio;
    while (p)
    {
        if (p->adj == v2)
            return true;
        p = p->prox;
    }
    return false;
}

bool insereAresta(Vertice *g, int v1, int v2, int p)
{
    NO *ant;
    if (existeAresta(g, v1, v2, &ant))
        return false;
    NO *novo = (NO *)malloc(sizeof(NO));
    novo->adj = v2;
    novo->prox = g[v1].inicio;
    novo->peso = p;
    g[v1].inicio = novo;
    return true;
}

bool ArestasEmG1(Vertice *g1, Vertice *g2)
{
    NO *ant;
    for (int i = 1; i <= V; i++)
    {
        NO *p = g2[i].inicio;
        while (p)
        {
            if (!existeAresta(g1, i, p->adj, &ant))
                return false;
            p = p->prox;
        }
    }
    return true;
}

Vertice *copia(Vertice *g)
{
    Vertice *resp = (Vertice *)malloc((V + 1) * sizeof(Vertice));
    inicializar(resp);
    for (int i = 1; i <= V; i++)
    {
        NO *p = g[i].inicio;
        while (p)
        {
            NO *novo = (NO *)malloc(sizeof(NO));
            novo->adj = p->adj;          // = i (transposta)
            novo->prox = resp[i].inicio; // = resp[p->adj].inicio (transposta)
            resp[i].inicio = novo;       // resp[p->adj].inicio = novo
            p = p->prox;
        }
    }
    return resp;
}
