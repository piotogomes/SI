#include <stdio.h>
#include <stdlib.h>

void bubble(int v[], int tam) {

    for (int ult = tam - 1; ult > 0; ult--){
        for (int i = 0; i < ult; i++){
            int aux;
            if (v[i] > v[i+1]){
                aux = v[i+1];
                v[i+1] = v[i];
                v[i] = aux;
            }
        }
    }
}

void selection(int v[], int tam) {

    for (int j = 0; j < tam; j++){
        int min = v[j];
        int aux = j;
        for (int i = j; i < tam; i++){
            if(v[i] < min) {
                min = v[i];
                aux = i;
            }
        }
        v[aux] = v[j];
        v[j] = min;
    }
}

void quick(int v[], int inicio, int fim) {
    if (inicio >= fim) return;
    int p = v[fim];
    int i = inicio;
    for (int j = inicio; j < fim; j++) {
        if(v[j] < p) {
            int aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
        }
    }
    int aux = v[i];
    v[i] = v[fim];
    v[fim] = aux;
    quick(v, inicio, i - 1);
    quick(v, i + 1, fim);
}

int main() {

    int tam; 
    printf("Insira o tamanho da lista: ");
    scanf("%d", &tam);
    int* v = (int*) malloc(sizeof(int)*tam);
    printf("Insira os elementos da lista: ");
    for (int i = 0; i < tam; i++){
        scanf("%d", &v[i]);
    }
    // bubble(v, tam);
    printf("Bubble ");
    for (int i = 0; i < tam; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
    // selection(v, tam);
    printf("Selection ");
    for (int i = 0; i < tam; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
    quick(v, 0, tam - 1);
    for (int i = 0; i < tam; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
    free(v);


    return 0;
}