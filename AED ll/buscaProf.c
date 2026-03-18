#include "grafoAPI.h"

void visitaProfEC(Grafo *g, int v1, int v2, int *cor, int *desc, int *term, int *ant, int *tempo, bool *resp)
{
    cor[v1] = 1; // deixa cinza
    desc[v1] = ++(*tempo);
    for (ApontadorVertAdj u = primeiroListaAdj(g, v1); u != ARESTA_NULA; u = proxListaAdj(g, v1, u))
    {
        if (cor[idVertice(g, u)] == 0)
        {
            printf("vertice u: %d\n", idVertice(g,u)); 
            if (idVertice(g, u) == v2)
                *resp = true;
            ant[idVertice(g, u)] = v1;
            visitaProfEC(g, idVertice(g, u), v2, cor, desc, term, ant, tempo, resp);
        }
    }
    term[v1] = ++(*tempo);
    cor[v1] = 2;
}

bool existeCaminho(Grafo *g, int v1, int v2)
{

    // malloc dos vetores cor, descoberta, termino e anterior
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
    bool resp = false;
    visitaProfEC(g, v1, v2, cor, desc, term, ant, &tempo, &resp);
    if (resp) imprimeCaminho(v1, v2, ant);
    return resp;
}

void imprimeCaminho(int v1, int v2, int ant[])
{
    if (v1 == v2)
    {
        printf("%d ", v1);
        return;
    }
    else {
        imprimeCaminho(v1, ant[v2], ant);
        printf("%d ", v2);
    }
}


















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



void buscaProfundidade(Grafo *g)
{
    // malloc dos vetores cor, descoberta, termino e anterior
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

    for (int i = 0; i < g->numVer; i++)
    {
        if (cor[i] == 0)
        {
            visitaProf(g, i, cor, desc, term, ant, &tempo);
        }
    }
}