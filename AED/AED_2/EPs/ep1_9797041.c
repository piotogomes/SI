#ifdef MATRIZ
#include "grafo_matrizadj.c"
#else
#include "grafo_listaadj.c"
#endif

#include "helpers.c"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// função para imprimir na saida corretamente

void imprimirArq(Grafo *g, FILE *saida, int ant[], int ult)
{

    float soma = 0;
    for (int i = 0; i < g->numVer; i++)
    {
        if (ant[i] != -1)
        {
            soma += (pesoAresta(g, i, ant[i]));
        }
    }
    fprintf(saida, "%.1f\n%d\n", soma, ult);
    for (int i = 0; i < g->numVer; i++)
    {
        for (ApontadorVertAdj u = primeiroListaAdj(&agm, i); u != ARESTA_NULA; u = proxListaAdj(&agm, i, u))
        {

            if (i < idVertice(&agm, u))
            {
                fprintf(saida, "%d %d %.1f\n", i, idVertice(&agm, u), pesoAresta(g, i, idVertice(&agm, u)));
            }
        }
    }
}

void agmPrim(Grafo *g, int raiz, int **resp, int *ult)
{
    Peso chPeso[g->numVer];
    int ant[g->numVer];
    Heap fila;
    criarFila(&fila, g->numVer);

    for (int i = 0; i < g->numVer; i++)
    {
        chPeso[i] = __INT_MAX__;
        ant[i] = -1;
    }
    chPeso[raiz] = 0;
    ant[raiz] = -1;
    subirMin(&fila, posNaFila(&fila, raiz), chPeso);

    while (tamFila(&fila) > 0)
    {
        int v = extrairFila(&fila, chPeso);
        if (tamFila(&fila) == 0)
        {
            *ult = v;
        }
        for (ApontadorVertAdj u = primeiroListaAdj(g, v); u != ARESTA_NULA; u = proxListaAdj(g, v, u))
        {
            int t = idVertice(g, u);

            if (pertenceFila(&fila, t) && (pesoAresta(g, v, t) < chPeso[t]))
            {
                ant[t] = v;
                chPeso[t] = pesoAresta(g, v, t);
                subirMin(&fila, posNaFila(&fila, t), chPeso);
            }
        }
    }
    *resp = ant;
}

bool verifica_validade_vertice(Grafo *g, int v)
{
    return false ? (v < 0 || v > g->numVer) : true;
}

bool le_grafo(FILE *entrada, FILE *saida, Grafo *g, int v, int a)
{

    bool resp = true;
    for (int i = a; i > 0; i--)
    {
        int v1, v2;
        Peso p;
        fscanf(entrada, "%d %d %f", &v1, &v2, &p);
        if (!verifica_validade_vertice(g, v1))
        {
            fprintf(saida, "ERRO: VERTICE INVALIDO (%d)\n", v1);
        }
        if (!verifica_validade_vertice(g, v2))
        {
            fprintf(saida, "ERRO: VERTICE INVALIDO (%d)\n", v2);
        }
        if (v1 == v2)
        {
            fprintf(saida, "ERRO: AUTO-LACO (%d,%d)\n", v1, v2);
        }
        if (existeAresta(&g, v1, v2))
        {
            fprintf(saida, "ERRO: ARESTA PARALELA\n");
        }
        if (p <= 0)
        {
            fprintf(saida, "ERRO: PESO INVALIDO\n");
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *entrada = fopen(argv[1], "rt");
    FILE *saida = fopen(argv[2], "wt");

    int v;
    int a;
    int *resp;
    int ult;
    Grafo g;
    fscanf(entrada, "%d %d", &v, &a);

    inicializarGrafoAdj(&g, v);

    for (int i = a; i > 0; i--)
    {
        int v1, v2;
        Peso p;
        fscanf(entrada, "%d %d %f", &v1, &v2, &p);
        if (p <= 0)
        {
            fprintf(saida, "ERRO: PESO INVALIDO\n");
            continue;
        }
        if (existeAresta(&g, v1, v2))
        {
            fprintf(saida, "ERRO: ARESTA PARALELA\n");
            continue;
        }
        if (v1 == v2)
        {
            fprintf(saida, "ERRO: AUTO-LACO\n");
            continue;
        }
        if (v1 < 0 || v2 < 0 || v1 >= v || v2 >= v)
        {
            fprintf(saida, "ERRO: VERTICE INVALIDO\n");
            continue;
        }
        insereArestaND(&g, v1, v2, p);
    }
    if (!grafoConexoND(&g))
    {
        fopen(argv[2], "w"); // deixa em branco
        fprintf(saida, "ERRO: GRAFO NAO CONECTADO\n");
        return -1;
    }
    agmPrim(&g, 0, &resp, &ult);
    // imprimeGrafoND(&g);

    imprimirArq(&g, saida, resp, ult);

    fclose(entrada);
    fclose(saida);
}