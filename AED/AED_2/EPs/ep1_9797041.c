#ifdef MATRIZ
#include "grafo_matrizadj.c"
#else
#include "grafo_listaadj.c"
#endif

#include "helpers.c"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    FILE* entrada = fopen(argv[1],"rt");
    FILE* saida = fopen(argv[2],"wt");

    int v;
    int a;
    Grafo g;
    fscanf(entrada, "%d %d", &v, &a);

    inicializarGrafoAdj(&g, v);

    for(int i = a; i > 0; i--) {
        int v1, v2;
        Peso p;
        fscanf(entrada, "%d %d %f", &v1, &v2, &p);
        if(p <= 0) {
            fprintf(saida, "ERRO: PESO INVALIDO\n");
            continue;
        }
        printf("%d %d %f\n", v1, v2, p);
        if(existeAresta(&g, v1, v2)) {
            fprintf(saida, "ERRO: ARESTA PARALELA\n");
            continue;
        }
        insereArestaND(&g, v1, v2, p);
    }
    imprimeGrafo(&g);



    fclose(entrada);
    fclose(saida);
}