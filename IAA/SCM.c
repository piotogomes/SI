#include <stdio.h>
#include <stdlib.h>







void scm_r(int i, int f, float seq[], int n, float* res) {
    if (i >= n) return; // Caso base: passou do fim
    if (f >= n) {
        scm_r(i + 1, i + 1, seq, n, res); // Próximo início
        return;
    }
    // Calcula soma do subarray seq[i..f]
    float soma = 0;
    for (int k = i; k <= f; k++) {
        soma += seq[k];
    }
    if (soma > *res) {
        *res = soma;
    }
    // printf("res: %f\n", *res);
    scm_r(i, f + 1, seq, n, res); // Avança o fim
}

float scm_i(float seq[], int n, int* resp) {
    float sufMax = 0;
    float seqMax = 0;
    int ini = 0;
    for(int i  = 0; i < n; i++) {
        if(sufMax + seq[i] > seqMax){
            sufMax = sufMax + seq[i];
            seqMax = sufMax;
            resp[0] = ini;
            resp[1] = i;
        }
        else {
            if(sufMax + seq[i] > 0) {
                sufMax = sufMax + seq[i];
            }
            else {
                ini = i + 1;
                sufMax = 0;
            }
        }
    }
    return seqMax;

}


int main() {

    float v[7] = {4, 1.5, -1, 3, -2, -3, 3};
    int* resp = (int*) malloc(sizeof(int)*2);
    for(int i = 0; i < 2; i++) {
        resp[i] = 0;
    }
    printf("%f\n", scm_i(v, 7, resp));
    float res = 0;
    scm_r(0, 0, v, 7, &res);
    printf("%f\n", res);


    return 0;
}