#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void solve(){
    int m;
    scanf("%d", &m);
    int buffer = 100000;
    char linha[buffer];
    char resposta[buffer];
    int valido = 1;

    while(m > 0) {
        scanf("%s", linha);
        char* esq = strstr(linha, "ESQUERDA");
        char* dir = strstr(linha, "DIREITA");
        if(esq == NULL && dir == NULL) {
            printf("Ahn? Acho que escolhemos o tunel errado...\n");
            while(m > 1) {
                scanf("%s", linha);
                m--;
            }
            valido = 0;
            return;
        }
        if(esq != NULL) {
            char* resto = strstr(esq, "DIREITA");
            if(resto != NULL || valido == 0) {
                printf("Ahn? Acho que escolhemos o tunel errado...\n");
                valido = 0;
                return;

            }
            else {
                strcat(resposta, "ESQUERDA ");
            }
        }
        
        if(dir != NULL) {
            char* resto = strstr(dir, "ESQUERDA");
            if(resto != NULL || valido == 0) {
                printf("Ahn? Acho que escolhemos o tunel errado...\n");
                valido = 0;
                return;
            }
            else {
                strcat(resposta, "DIREITA ");
                
            }
        
        }
        m--;
    }
    if(valido) printf("%sESPERE POR NOS CORUJINHA!!!\n", resposta);


}

int main(){
    int n;
    scanf("%i", &n);

    while(n--){
        solve();
    }
    return 0;
}