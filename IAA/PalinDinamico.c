#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* maiorPalin(char* seq, int n, int* resp) {



    char** matriz = (char**) malloc(sizeof(char*)*n);
    for(int i = 0; i < n; i++) {
       matriz[i] = (char*) malloc(sizeof(char) * n);
    }
    
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
        {
            if(seq[j] == seq[i]) {
                if(i-1 >= 0 && j+1 < n) matriz[i][j] = matriz[i-1][j+1] + 1;
                else matriz[i][j] = 1; 
                if(resp[0] < matriz[i][j]) {
                    resp[0] = matriz[i][j];
                    resp[1] = i;
                    resp[2] = j;
                }
            }
            else matriz[i][j] = 0;
        }
    }
    return resp;
    
    
    
    
    
}


int main() {
    
    
    int resp[3] = {0, 0, 0};
    char seq[16];
    scanf("%s", seq);
    printf("%d\n", maiorPalin(seq, strlen(seq), resp)[0]);








    return 0;
}