#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s {
    int peso;
    int valor;
} Item;

void MenorPeso(Item* dados, float cap, int qtd, float resp[3]) {    
    // ordenar por menor peso
    for (int i = 0; i < qtd; i++)
    {
        for (int j = i + 1; j < qtd; j++)
        {
            if (dados[i].peso > dados[j].peso)
            {
                Item aux = dados[j];
                dados[j] = dados[i];
                dados[i] = aux;
            }
            if (dados[i].peso == dados[j].peso) // desempate
            {
                if (dados[i].valor < dados[j].valor)
                {
                    Item aux = dados[j];
                    dados[j] = dados[i];
                    dados[i] = aux;
                }
            }
        }
    }
    // encher a mochila
    for(int i = 0; i < qtd; i++) {
        if(dados[i].peso + resp[0] <= cap) {
            resp[0] += dados[i].peso;
            resp[1] += dados[i].valor;
            resp[2] += 1;
        }
    }
}

void MaiorValor(Item *dados, float cap, int qtd, float resp[3])
{
    // ordenar pelo maior valor
    for (int i = 0; i < qtd; i++)
    {
        for (int j = i + 1; j < qtd; j++)
        {
            if (dados[i].valor < dados[j].valor)
            {
                Item aux = dados[j];
                dados[j] = dados[i];
                dados[i] = aux;
            }
            if (dados[i].valor == dados[j].valor) //desempate
            {
                if (dados[i].peso > dados[j].peso)
                {
                    Item aux = dados[j];
                    dados[j] = dados[i];
                    dados[i] = aux;
                }
            }
        }
    }
    // encher a mochila
    for (int i = 0; i < qtd; i++)
    {
        if (dados[i].peso + resp[0] <= cap)
        {
            resp[0] += dados[i].peso;
            resp[1] += dados[i].valor;
            resp[2] += 1;
        }
    }
}

void MaiorValorPeso(Item *dados, float cap, int qtd, float resp[3])
{
    // ordenar pelo maior valor/peso
    for (int i = 0; i < qtd; i++)
    {
        for (int j = i + 1; j < qtd; j++)
        {
            if (dados[i].valor / dados[i].peso < dados[j].valor / dados[j].peso)
            {
                Item aux = dados[j];
                dados[j] = dados[i];
                dados[i] = aux;
            }
            if (dados[i].valor / dados[i].peso == dados[j].valor / dados[j].peso) // desempate
            {
                if (dados[i].peso < dados[j].peso)
                {
                    Item aux = dados[j];
                    dados[j] = dados[i];
                    dados[i] = aux;
                }
            }
        }
    }
    // encher a mochila
    for (int i = 0; i < qtd; i++)
    {
        if (dados[i].peso + resp[0] <= cap)
        {
            resp[0] += dados[i].peso;
            resp[1] += dados[i].valor;
            resp[2] += 1;
        }
    }
}

int main(int argc, char *argv[])
{

    FILE *entrada;
    FILE *saida;

    entrada = fopen(argv[1], "r");
    saida = fopen(argv[2], "w");
    float cap; 
    int qtd;
    fscanf(entrada, "%f %d", &cap, &qtd);

    Item dados[qtd];
    for (int i = 0; i < qtd; i++)
    {
        fscanf(entrada, "%d %d", &dados[i].peso, &dados[i].valor);
    }

    // for (int i = 0; i < qtd; i++)
    // {
    //     printf("%d %d \n", dados[i].peso, dados[i].valor);
    // }

    // chamadas
    float resp[3] = {0, 0, 0};
    MenorPeso(dados, cap, qtd, resp);
    fprintf(saida, "Testando Criterio de Selecao: 'Menor Peso'\n"); 
    fprintf(saida, "Peso maximo:    %.1f\n", cap);
    fprintf(saida, "Peso usado:    %.1f\n", resp[0]);
    fprintf(saida, "Valor carregado:    %.1f\n", resp[1]);
    fprintf(saida, "Numero de objetos:    %.0f\n\n", resp[2]);

    resp[0] = resp[1] = resp[2] = 0;

    MaiorValor(dados, cap, qtd, resp);
    fprintf(saida, "Testando Criterio de Selecao: 'Maior Valor'\n");
    fprintf(saida, "Peso maximo:    %.1f\n", cap);
    fprintf(saida, "Peso usado:    %.1f\n", resp[0]);
    fprintf(saida, "Valor carregado:    %.1f\n", resp[1]);
    fprintf(saida, "Numero de objetos:    %.0f\n\n", resp[2]);

    resp[0] = resp[1] = resp[2] = 0;

    MaiorValorPeso(dados, cap, qtd, resp);
    fprintf(saida, "Testando Criterio de Selecao: 'Maior Valor Dividido pelo Peso'\n");
    fprintf(saida, "Peso maximo:    %.1f\n", cap);
    fprintf(saida, "Peso usado:    %.1f\n", resp[0]);
    fprintf(saida, "Valor carregado:    %.1f\n", resp[1]);
    fprintf(saida, "Numero de objetos:    %.0f\n", resp[2]);
    // Escrever na saída corretamente

 
    fclose(entrada);
    fclose(saida);
    // frees
    return 0;
}
