#ifndef API_H
#define API_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAXVER 100
typedef int Peso;

#ifdef MATRIZ
#define ARESTA_NULA -1
typedef int ApontadorVertAdj;
typedef struct
{

    Peso matriz[MAXVER][MAXVER];
    int numVer;

} Grafo;
#endif

#ifdef LISTA

#define ARESTA_NULA NULL
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
typedef Aresta *ApontadorVertAdj;

#endif

void verificarVertice(Grafo *g, int v);

int idVertice(Grafo *g, ApontadorVertAdj v);

bool inicializarGrafoAdj(Grafo *g, int numVer);

bool existeAresta(Grafo *g, int v1, int v2);

void insereAresta(Grafo *g, int v1, int v2, Peso p);

void insereArestaND(Grafo *g, int v1, int v2, Peso p); // ND == não direcionado

bool removerAresta(Grafo *g, int v1, int v2, Peso *p);

bool listaAdjVazia(Grafo *g, int v);

ApontadorVertAdj proxListaAdj(Grafo *g, int v, ApontadorVertAdj atual);

ApontadorVertAdj primeiroListaAdj(Grafo *g, int v);

void liberaGrafo(Grafo *g);

void imprimeGrafo(Grafo *g);

bool existeCaminho(Grafo *g, int v1, int v2);

void imprimeCaminho(int v1, int v2, int *ant);

void menorCaminho(Grafo *g, int v1, int v2);

bool grafoAciclico(Grafo *g); // implementar e imprimir um cliclo

bool grafoConexoND(Grafo *g);

void visitaProf(Grafo *g, int v, int *cor, int *desc, int *term, int *ant, int *tempo);

// ordenação topologica, lista decrescente em função do tempo de termino, implementar e imprimir

// quantos componentes conectados e quais são eles

#endif
