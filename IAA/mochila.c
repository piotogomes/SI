#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s {
    bool exist;
    bool belong;
} P;

P** solve(int S[], int n, int K, P** matriz) {
    matriz[0][0].exist = true;
    for(int j = 1; j < K; j++) {
        matriz[0][j].exist = false;
    }
    for(int i = 1; i < n; i++){
        for(int j = 0; j < K; j++) {
            matriz[i][j].exist = false;
            if(matriz[i-1][j].exist) {
                matriz[i][j].exist = true;
                matriz[i][j].belong = false;
            }
            else {
                if(j - S[i] >= 0) {
                    if(matriz[i-1][j - S[i]].exist) {
                        matriz[i][j].exist = true;
                        matriz[i][j].belong = true;
                    }
                }
            }
        }
    }
    return matriz;


}




int main () {
    int n;
    P** matriz = (P**) malloc(sizeof(P*));
    for(int i = 0; i < n; i++) {
        matriz[i] = (P*) malloc(sizeof(P)); 
    }






    return 0;
}