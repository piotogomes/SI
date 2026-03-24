#include "./AED_2/grafoAPI.h"

int main() {

    Grafo g;
    inicializarGrafoAdj(&g, 4);
    insereArestaND(&g, 0, 1, 23);
    insereArestaND(&g, 2, 3, 1);
    insereArestaND(&g, 2, 1, 123);
    printf("\n-------------------------------\n");
    imprimeGrafo(&g);
    if(grafoConexoND(&g)) printf("conexooxoox");
    int v1 = 3;
    int v2 = 6;

    

    return 0;
}

