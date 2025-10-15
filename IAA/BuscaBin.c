#include <stdio.h>
#include <stdlib.h>



int buscaBin(int v[], int ini, int fim, int ch) {
    if(ini >= fim) {
        if(v[ini] == ch) return ini;
        return -1;
    }
    int meio = (ini + fim) / 2;
    if(v[meio] == ch) return meio;
    if(v[meio] > ch) return buscaBin(v, ini, meio - 1, ch);
    if(v[meio] < ch) return buscaBin(v, meio + 1, fim, ch);
}





int main () {


    int v[6] = {-2, 3, 5, 7, 99, 984};
    printf("%d\n", buscaBin(v, 0, 5, 3));



    return 0;
}