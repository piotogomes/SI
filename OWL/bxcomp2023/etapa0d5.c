#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



int menorSoma(char matriz[6][11], int lin, int col) {
    int somamenor = 0;
    int soma = 0;


    for(int i = 0; isalpha(matriz[i][col]) == 0; i++) {
        somamenor += (int) matriz[i][col] - 48;
        
    }
    for(int i = 5; isalpha(matriz[i][col]) == 0; i--) {
        soma += (int) matriz[i][col] - 48;
        
    }
    if(somamenor>soma){
        somamenor=soma;
    }   
    soma = 0;
    for(int i = 0; isalpha(matriz[lin][i]) == 0; i++) {
        soma += (int) matriz[lin][i] - 48;
    }
    if(somamenor>soma){
        somamenor=soma;
    }   
    soma = 0;
    
    
    for(int i = 9; isalpha(matriz[lin][i]) == 0; i--) {
        soma += (int) matriz[lin][i] - 48;
        printf("matriz i j %d\n", matriz[lin][i] - 48);
    }
    if(somamenor>soma){
        somamenor=soma;
    }   
    printf("%d soma menor", somamenor);
    return somamenor;

}

void main() {

    int t;
    scanf("%d\n", &t);
    for(int i = 0; i < t; i++){
        char matriz[6][11];
        int soma = 0;
        int letra = 0;
        for(int i = 0; i < 6; i++) {
            for(int j = 0; j < 11; j++) {
                scanf("%c", &matriz[i][j]);
                // printf("%d ", matriz[i][j]);
            }
        }
        int posx;
        int posy;
        for(int i = 0; i < 6; i++) {
            for(int j = 0; j < 10; j++) {
                // printf("%d ", matriz[i][j]);
                if(isalpha(matriz[i][j]) != 0) {
                    letra = 1;
                    posx = i;
                    posy = j;
                }
                else {
                    soma += (int) matriz[i][j] - 48;
                    // printf("%d\n", soma);
                }
            }
        }
        if(letra == 0) {
        printf("Nossa, cheio de predas, consegui %d pontos.", soma);
        }   
            
        if(matriz[posx][posy] == 'C') {
            printf("Opa, achei o item, Paodo-Competech2077, esta na posicao %dx%d, terei que fazer %d pontos para conseguir chegar la.\n", posx, posy, menorSoma(matriz, posx, posy));
            
        }
        if(matriz[posx][posy] == 'F') {
            printf("Opa, achei o item, Nitrato de Fala coruja297, esta na posicao %dx%d, terei que fazer %d pontos para conseguir chegar la.\n", posx, posy, menorSoma(matriz, posx, posy));
            
        }
        if(matriz[posx][posy] == 'O') {
            printf("Opa, achei o item, O2wlficiNASA, esta na posicao %dx%d, terei que fazer %d pontos para conseguir chegar la.\n", posx, posy, menorSoma(matriz, posx, posy));
            
        }
        if(matriz[posx][posy] == 'G') {
            printf("Opa, achei o item, GTX-Grace 4090, esta na posicao %dx%d, terei que fazer %d pontos para conseguir chegar la.\n", posx, posy, menorSoma(matriz, posx, posy));
            
        }
    }
    return;
}