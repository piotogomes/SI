#include <stdio.h>
#include <stdbool.h>
#include <iostream>

void rotaciona(int** m, int row, int col) {
    int prof = 0;
    int atual;
    int prox;
    while(prof < row / 2) {
        int i, j = prof;
        atual = m[i][j];
        for(; i < row - prof - 1; i++){
            prox = m[i+1][j];
            m[i+1][j] = atual;
            atual = prox;
        }
        i++;
        for(; j < col - prof - 1; j++) {
            prox = m[i][j+1];
            m[i][j+1] = m[i][j];
            atual = prox;
        }
        j++;
        for(; i > prof; i--){
            prox = m[i-1][j];
            m[i-1][j] = atual;
            atual = prox;
        }
        i--;
        for(; j > prof; j--) {
            prox = m[i][j-1];
            m[i][j-1] = m[i][j];
            atual = prox;
        }
        j--;
    }
}

int main(int argc, char *argv[])
{

    int row, col, r;
    scanf("%d %d %d", &row, &col, &r);
    int matrix[row][col];
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            scanf("%d", &matrix[i][j]);
        }
    }






    for(int i = 0; i < row; i++){
        for(int j = 0; j < row; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
            
    }
    return 0;
}