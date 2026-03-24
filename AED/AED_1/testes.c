#include <stdio.h>
#include <stdbool.h>
#include "listas.h"

// trocar de posição uma chave ch com o prox elemento ok
// verificar se 2 ListaLigEsts sao identicas ok
// verificar se uma ListaLigEst seq l1 é identica a ListaLigEst ligada l2 ok
// em uma ListaLigEst ligada com repetição, excluir todas as ocorrencias de uma chave

int main()
{
    ListaCr *l = (ListaCr *)malloc(sizeof(ListaCr));
    NOListaCr *p = (NOListaCr *)malloc(sizeof(NOListaCr));
    NOListaCr *esq;
    NOListaCr *acima;
    inicializar_LC(l);
    for(int i = 0; i < 20; i++) {
        inserir_LC(i, i, 1, l);
    }

    for (int i = 0; i < MAX; i++)
    {
        NOListaCr *atual = l->lin[i];
        if(!atual) {
            for(int j = 0; j < MAX - 1; j++) {
                printf("0 ");
            }
        }
        else {
            int cont = 0;
            while(atual){
                for (int j = cont; j < atual->c; j++)
                {
                    printf("0 ");
                    cont++;
                }
                printf("%d ", atual->chave);
                if(atual->proxCol) {
                    cont = atual->proxCol->c - atual->c;
                }
                atual = atual->proxCol;
                
            }
            for (int j = cont; j < MAX - 1; j++)
            {
                printf("0 ");
            }
        }
        printf("\n");
    }

    return 0;
}