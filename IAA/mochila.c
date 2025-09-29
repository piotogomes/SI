#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s {
    bool exist;
    bool belong;
} P;

P** solve(int S[], int n, int K, P** matriz) {
    matriz[0][0].exist = true;
    for(int j = 1; j <= K; j++) {
        matriz[0][j].exist = false;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= K; j++) {
            matriz[i][j].exist = false;
            if(matriz[i-1][j].exist) {
                matriz[i][j].exist = true;
                matriz[i][j].belong = false;
            }
            else {
                if(j - S[i - 1] >= 0) {
                    if(matriz[i-1][j - S[i-1]].exist) {
                        matriz[i][j].exist = true;
                        matriz[i][j].belong = true;
                    }
                }
            }
        }
    }
    for (int i = 0; i <= n; i++)
    { 
        for (int j = 0; j <= K; j++)
        {
            printf("[%d][%d] ", matriz[i][j].exist, matriz[i][j].belong);
        }
        printf("\n");
    }
    return matriz;


}




int main () {
    int n = 4;
    int S[4] = {2, 3, 5, 7};
    int K = 9;
    int resp[4];
    int count = 0;
    P** matriz = (P**) malloc(sizeof(P*)*n);
    for(int i = 0; i <= n; i++) {
        matriz[i] = (P*) malloc(sizeof(P)*K); 
    }
    solve(S, n, K, matriz);
    for (int j = K; j >= 0; j--)
    {
        for (int i = n; i >= 0; i--)
        {
            if (matriz[i][j].belong && matriz[i][j].exist) {
                resp[count] = S[i-1];
                j = j - S[i-1];
            }
            else resp[count] = -1;
            count++;
        }

    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", resp[i]);
    }
    return 0;
}