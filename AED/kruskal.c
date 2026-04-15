#include "./AED_2/grafoAPI.h"



typedef struct s{

    int x;
    struct s *p;
    int rank;
} UnionFind;


void makeSet(UnionFind* v, int x) {
    v->x = x;
    v->p->x = x;
    v->rank = 0;

}


void link(UnionFind* raiz1, UnionFind* raiz2) {

    if(raiz1->rank > raiz2->rank) {
        raiz2->p->x = raiz1->x;
    }
    else {
        raiz1->p->x = raiz2->x;
        if (raiz1->rank == raiz2->rank) {
            raiz2->rank += 1;
        }
    }
}

void unionTree(UnionFind* v1, UnionFind* v2) {
    link(findSet(v1), findSet(v2));
}

int findSet(UnionFind* v) {
    if(v->p->x != v->x) {
        v->p->x = findSet(v->p);       
    }
    return v->p->x;
}



int* kruskal(Grafo* g) {
    int* A = (int*) malloc(sizeof(int));
    for(ApontadorVertAdj u = primeiroListaAdj(g, v); u != ARESTA_NULA; u = proxListaAdj(g, v, u))
}