#include "grafoAPI.h"

int main() {

    Grafo g;
    inicializarGrafoAdj(&g, 10);
    insereAresta(&g, 1, 2, 123);
    insereAresta(&g, 2, 3, 123);
    insereAresta(&g, 3, 4, 123);
    insereAresta(&g, 4, 1, 123);
    printf("\n-------------------------------\n");
    imprimeGrafo(&g);
    if(existeCaminho(&g, 2, 1)) printf("sim tem caminho\n");


    return 0;
}

