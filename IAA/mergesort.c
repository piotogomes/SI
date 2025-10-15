#include <stdio.h>
#include <stdlib.h>



void merge(int v[], int ini, int fim) {
    if(ini >= fim) {
        return;
    }
    int meio = (ini + fim) / 2;
    merge(v, ini, meio);
    merge(v, meio + 1, fim);
    int n1 = meio - ini + 1;
    int n2 = fim - meio;
    int esq[n1];
    int dir[n2];
    for(int i = 0; i < n1; i++) {
        esq[i] = v[ini + i];
    }   
    for(int i = 0; i < n2; i++) {
        dir[i] = v[meio + i + 1];
    }
    int iterEsq = 0;
    int iterDir = 0;
    int k = ini;
    while(iterEsq < n1 && iterDir < n2){
        if(esq[iterEsq] <= dir[iterDir]){
            v[k] = esq[iterEsq];
            iterEsq++;
        }
        else {
            v[k] = dir[iterDir];
            iterDir++;
        }
        k++;
    }
    while(iterEsq < n1) {
        v[k] = esq[iterEsq];
        iterEsq++;
        k++;
    }
    while(iterDir < n2) {
        v[k] = dir[iterDir];
        iterDir++;
        k++;

    }

}





int main () {


    int v[6] = {-2, 3, 5, 7, 99, 984};
    merge(v, 0, 5);
    for(int i = 0; i < 6; i++) {

        printf("%d ", v[i]);

    }
    printf("\n");



    return 0;
}