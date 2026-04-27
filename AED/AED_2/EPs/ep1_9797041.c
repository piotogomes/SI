#ifdef MATRIZ
#include "grafo_matrizadj.c"
#else
#include "grafo_listaadj.c"
#endif

#include "helpers.c"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

// função para imprimir na saida corretamente

void imprimirArq(Grafo *g, FILE *saida, int ant[])
{
    Grafo agm;
    inicializarGrafoAdj(&agm, g->numVer);
    for (int i = 1; i < g->numVer; i++)
    {
        insereArestaND(&agm, i, ant[i], pesoAresta(g, i, ant[i]));
    }
    float soma = 0;
    int aux[g->numVer];
    int maisLonge = verticeMaisLonge(&agm);
    for (int i = 0; i < g->numVer; i++)
    {
        if (ant[i] != -1)
        {
            soma += (pesoAresta(g, i, ant[i]));
        }
        aux[i] = ant[i];
    }
    fprintf(saida, "%.1f\n%d\n", soma, maisLonge);
    // criar ordenação
    int orderIndex[g->numVer - 1];
    for (int i = 0; i < g->numVer - 1; i++)
    {
        int menor = INT_MAX;
        for (int j = 1; j < g->numVer; j++)
        {
            // percorre valores
            if (aux[j] < menor)
            {
                menor = aux[j];
            }
            // percorre indices
            if (j < menor)
            {
                if (aux[j] != INT_MAX)
                {
                    menor = j;
                }
            }
        }
        for (int j = 1; j < g->numVer; j++)
        {
            if ((aux[j] != INT_MAX) && ((aux[j] == menor) || (j == menor)))
            {
                orderIndex[i] = j;
                aux[j] = INT_MAX;
                break;
            }
        }
    }
    // imprime no arquivo ordenado
    for (int i = 0; i < g->numVer - 1; i++)
    {
        if (ant[orderIndex[i]] < orderIndex[i])
        {
            fprintf(saida, "%d %d %.1f\n", ant[orderIndex[i]], orderIndex[i], pesoAresta(g, ant[orderIndex[i]], orderIndex[i]));
        }
        else
        {
            fprintf(saida, "%d %d %.1f\n", orderIndex[i], ant[orderIndex[i]], pesoAresta(g, ant[orderIndex[i]], orderIndex[i]));
        }
    }
}

//função prim

int *agmPrim(Grafo *g, int raiz)
{
    Peso chPeso[g->numVer];
    int *ant = malloc(sizeof(int) * g->numVer);
    Heap fila;
    criarFila(&fila, g->numVer); // cria o heap

    for (int i = 0; i < g->numVer; i++)
    {
        chPeso[i] = FLT_MAX;
        ant[i] = -1;
    }
    chPeso[raiz] = 0;
    ant[raiz] = -1;
    subirMin(&fila, posNaFila(&fila, raiz), chPeso); // atualiza a raiz no heap

    while (tamFila(&fila) > 0)
    {
        int v = extrairFila(&fila, chPeso);
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
    return ant;
}

bool verifica_validade_vertice(int v, int numVer)
{
    if (v < 0)
        return false;
    if (v >= numVer)
        return false;
    return true;
}

bool le_grafo(FILE *entrada, FILE *saida, Grafo *g, int v, int a)
{

    bool resp = true;
    for (int i = a; i > 0; i--)
    {
        int v1, v2;
        Peso p;
        fscanf(entrada, "%d %d %f", &v1, &v2, &p);
        if (!verifica_validade_vertice(v1, v))
        {
            fprintf(saida, "ERRO: VERTICE INVALIDO (%d)\n", v1);
            resp = false;
        }
        if (!verifica_validade_vertice(v2, v))
        {
            fprintf(saida, "ERRO: VERTICE INVALIDO (%d)\n", v2);
            resp = false;
        }
        if (v1 == v2)
        {
            fprintf(saida, "ERRO: AUTO-LACO (%d,%d)\n", v1, v2);
            resp = false;
        }

        if (existeAresta(g, v1, v2))
        {
            if (v1 < v2)
                fprintf(saida, "ERRO: ARESTA PARALELA (%d,%d)\n", v1, v2);
            else
                fprintf(saida, "ERRO: ARESTA PARALELA (%d,%d)\n", v2, v1);
            resp = false;
        }
        if (p <= 0)
        {
            fprintf(saida, "ERRO: PESO INVALIDO (%.1f)\n", p);
            resp = false;
        }
        if (verifica_validade_vertice(v1, v) && verifica_validade_vertice(v2, v))
        {
            insereArestaND(g, v1, v2, p);
        }
    }
    return resp;
}

// DEBUG
// void imprimeGrafoAGM(Grafo *g, int ant[])
// {
//     Grafo agm;
//     inicializarGrafoAdj(&agm, g->numVer);
//     for (int i = 1; i < g->numVer; i++)
//     {
//         insereArestaND(&agm, i, ant[i], pesoAresta(g, i, ant[i]));
//     }
//     imprimeGrafoND(&agm);
// }

int main(int argc, char *argv[])
{
    FILE *entrada = fopen(argv[1], "rt");
    FILE *saida = fopen(argv[2], "wt");

    int v;
    int a;
    int *resp;
    bool erro = false;
    Grafo g;
    fscanf(entrada, "%d %d", &v, &a);

    inicializarGrafoAdj(&g, v);
    bool sucesso = le_grafo(entrada, saida, &g, v, a);

    if (sucesso && !grafoConexoND(&g))
    {
        fprintf(saida, "ERRO: GRAFO NAO CONECTADO\n");
        return -1;
    }

    if (sucesso && grafoConexoND)
    {
        resp = agmPrim(&g, 0);
        imprimirArq(&g, saida, resp);
    }

    free(resp);
    fclose(entrada);
    fclose(saida);


    return 0;
}