#include <stdio.h>
#include <stdbool.h>


typedef struct s {
    int saida;
    int chegada;
    bool resp = false;
} Rota;




void solve() {
    int qtd, nrTest;
    scanf("%d %d", &qtd, &nrTest);
    int est[qtd];
    for(int i = 0; i < qtd; i++) {
        scanf("%d ", &est[i]);
    }
    Rota testes[nrTest];
    for (int i = 0; i < nrTest; i++)
    {
        scanf("%d %d", &testes[i].chegada, &testes[i].saida);
    }
    for (int i = 0; i < nrTest; i++)
    {
        for(int j = 0; j < qtd || testes[i].resp; j++) {

        }
    }
}









int main(int argc, char *argv[])
{

    int n;
    scanf("%d", &n);
    while (n)
    {
        solve();
        n--;
    }

    return 0;
}