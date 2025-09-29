#include <stdio.h>
#include <stdlib.h>




void criarMatriz(int n) {
    int matriz[n][n];
    int aux = n - 1;
    int count = 0;
    while(aux > n / 2) {
        int linha = aux;
        int coluna = aux;
        while(coluna >= n - aux - 1) {
            matriz[linha][coluna] = (n*n - count);
            if(coluna == n - aux - 1) break;
            count++;
            coluna--;
        }
        while(linha >= n - aux - 1) {
            matriz[linha][coluna] = (n*n - count);
            if(linha == n - aux - 1) break;
            count++;
            linha--;
        }
        while(coluna <= aux) {
            matriz[linha][coluna] = n*n - count;
            if(coluna == aux) break;
            count++;
            coluna++;
        }
        while(linha <= aux) {
            if(linha == aux) break;
            matriz[linha][coluna] = n*n - count;
            count++;
            linha++;
        }
        aux--;
    }
    matriz[n/2][n/2] = 1;

    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    

}
void solve(){
    int i;
    scanf("%d", &i);
    criarMatriz(i);
}

int main(){
    int n;
    scanf("%i", &n);

    while(n--){
        solve();
    }
    return 0;
}