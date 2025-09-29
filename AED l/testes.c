#include <stdio.h>
#include <stdbool.h>
#include "listas.h"
#include <stdlib.h>



// trocar de posição uma chave ch com o prox elemento ok
// verificar se 2 ListaLigEsts sao identicas ok
// verificar se uma ListaLigEst seq l1 é identica a ListaLigEst ligada l2 ok
// em uma ListaLigEst ligada com repetição, excluir todas as ocorrencias de uma chave 



void main() {
    ListaLDS* l = (ListaLDS*) malloc(sizeof(ListaLDS));
    llds_inicializar(l);
    
    for(int i = 1; i < 10; i++){
        llds_inserir(l, i);
    }
    printf("aaaa\n");
    llds_exibir(l);
    llds_excluir(l, 4);
    llds_exibir(l);
    llds_inserir(l,10);
    llds_exibir(l);
    llds_excluir(l, 4);
    llds_exibir(l);


    return;
}