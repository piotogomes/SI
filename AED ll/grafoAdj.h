#include <stdio.h>
#include <stdbool.h>


#define Ver 100
#define Nulo -1
typedef int Peso;

typedef struct {

    Peso matriz[Ver][Ver];
    int numVer;

} Grafo;



Grafo inicializarGrafoAdj(int vert) {
    Grafo g;
    g.numVer = vert;
    for(int i = 0; i < vert; i++) {
       for(int j = 0; j < vert; j++) {
            g.matriz[i][j] = Nulo;
        }   
    }
    return g;
}


