#ifndef API_H
#define API_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAXVER 100
typedef int Peso;

#ifdef MATRIZ
typedef int ApontadorVertAdj;
typedef struct 
{

    Peso matriz[MAXVER][MAXVER];
    int numVer;

} Grafo;
#endif

#ifdef LISTA
typedef struct str
{
    int vadj;
    Peso p;
    struct str *prox;
} Aresta;

typedef struct 
{
    Aresta **listaAdj;
    int numVer;
} Grafo;

typedef Aresta* ApontadorVertAdj;
#endif

void verificarVertice(Grafo *g, int v);

bool inicializarGrafoAdj(Grafo *g, int numVer);

bool existeAresta(Grafo *g, int v1, int v2);

void insereAresta(Grafo *g, int v1, int v2, Peso p);

bool removerAresta(Grafo *g, int v1, int v2, Peso *p);

bool listaAdjVazia(Grafo *g, int v);

ApontadorVertAdj proxListaAdj(Grafo *g, int v, ApontadorVertAdj atual);

ApontadorVertAdj primeiroListaAdj(Grafo *g, int v);

void liberaGrafo(Grafo *g);

void imprimeGrafo(Grafo *g);

#endif
