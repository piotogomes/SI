#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int quadMax(int **matriz, int dimensao, int linha, int coluna, int **dados)
{
    // CASO BASE
    if (dimensao == 1)
    {
        dados[0][0] = dimensao; // sempre vai ser 1
        if (matriz[linha][coluna] == 1)
        {
            return 1; // pixel branco
        }
        else
        {
            return 0; // pixel preto
        }
    }
    // Recursão
    int novaDimensao = dimensao / 2;
    int a = quadMax(matriz, novaDimensao, linha, coluna, dados);
    int b = quadMax(matriz, novaDimensao, linha, coluna + novaDimensao, dados);
    int c = quadMax(matriz, novaDimensao, linha + novaDimensao, coluna, dados);
    int d = quadMax(matriz, novaDimensao, linha + novaDimensao, coluna + novaDimensao, dados);
    // atualiza a dimensão na matriz de dados
    dados[dimensao - 1][0] = dimensao;
    // Testes da recursão
    if ((a == b) && (a == c) && (a == d))
    {
        if (dimensao == dados[0][3]) // se a dimensão for igual a maxima e ainda sim todos os quadrantes são iguais
        {
            if (a == 1)
                dados[dimensao - 1][1]++;
            if (a == 0)
                dados[dimensao - 1][2]++;
        }
        return a;
    }
    else
    {
        if (a == 1)
            dados[novaDimensao - 1][1]++;
        if (a == 0)
            dados[novaDimensao - 1][2]++;
        if (b == 1)
            dados[novaDimensao - 1][1]++;
        if (b == 0)
            dados[novaDimensao - 1][2]++;
        if (c == 1)
            dados[novaDimensao - 1][1]++;
        if (c == 0)
            dados[novaDimensao - 1][2]++;
        if (d == 1)
            dados[novaDimensao - 1][1]++;
        if (d == 0)
            dados[novaDimensao - 1][2]++;
        return -1;
    };
}

int main(int argc, char *argv[])
{
    int dimensao = atoi(argv[1]);

    int **matriz = (int **)malloc(sizeof(int *) * dimensao);
    for (int i = 0; i < dimensao; i++)
    {
        matriz[i] = (int *)malloc(sizeof(int) * dimensao);
    }

    FILE *entrada;
    FILE *saida;
    int **dados = (int **)malloc(sizeof(int *) * dimensao);
    for (int i = 0; i < dimensao; i++)
    {
        dados[i] = (int *)malloc(sizeof(int) * 4);
    }
    // Dados : [[dimensão, branco, preto, dimensão total]
    //          [dimensão, branco, preto, 0]
    //          [dimensão, branco, preto, 0]
    //                               ...]
    for (int i = 0; i < dimensao; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            dados[i][j] = 0;
        }
    }
    dados[0][3] = dimensao; // guardar a dimensão total pra usar no teste da recursão
    // Arquivos
    entrada = fopen(argv[2], "r");
    saida = fopen("saida.txt", "w");
    for (int i = 0; i < dimensao; i++)
    {
        for (int j = 0; j < dimensao; j++)
        {
            matriz[i][j] = fgetc(entrada) - 48; // deixar em int, ASCII dos digitos 0 e 1 são 48 e 49 (poderia fazer a comparação com char..)
        }
        int aux = fgetc(entrada);
    }
    // chamada
    quadMax(matriz, dimensao, 0, 0, dados);
    // Escrever na saída corretamente
    while (dimensao > 0)
    {
        if (dados[dimensao - 1][0] != 0)
        {
            fprintf(saida, "%dx%d %d %d\n", dimensao, dimensao, dados[dimensao - 1][1], dados[dimensao - 1][2]);
        }
        dimensao--;
    }
    fclose(entrada);
    fclose(saida);
    // frees
    for (int i = 0; i < dimensao; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
    for (int i = 0; i < dimensao; i++)
    {
        free(dados[i]);
    }
    free(dados);
    return 0;
}
