#include <stdio.h>
#include <stdlib.h>

int SemiQuadradoMagico(int **matriz, int nlin, int ncol)
{
    int cte = 0;
    for (int i = 0; i < ncol; i++) // guarda a soma dos elementos da primeira linha (constante)
    {
        cte += matriz[0][i];
    }

    // Checa a soma das linhas
    for (int i = 0; i < nlin; i++)
    {
        int soma = 0;
        for (int j = 0; j < ncol; j++)
        {
            soma += matriz[i][j];
        }
        if (soma != cte)
            return 0;
    }
    // Checa a soma das colunas
    for (int i = 0; i < ncol; i++)
    {
        int soma = 0;
        for (int j = 0; j < nlin; j++)
        {
            soma += matriz[j][i];
        }

        if (soma != cte)
            return 0;
    }

    return 1;
}

int QuadradoMagico(int **matriz, int nlin, int ncol)
{

    if (SemiQuadradoMagico(matriz, nlin, ncol) == 0)
        return 0;
    int cte = 0;
    for (int i = 0; i < ncol; i++) // guarda a soma dos elementos da primeira linha (constante)
    {
        cte += matriz[0][i];
    }
    // Checa diagonal primaria
    int soma = 0;
    for (int i = 0; i < nlin; i++)
    {
        soma += matriz[i][i];
    }
    if (soma != cte)
        return 0;
    // Checa diagonal secundaria
    soma = 0;
    for (int i = 0, j = ncol - 1; i < nlin; i++, j--)
    {
        soma += matriz[i][j];
    }
    if (soma != cte)
        return 0;
    return 1;
}

int QuadradoMagicoAss(int **matriz, int nlin, int ncol)
{
    if (QuadradoMagico(matriz, nlin, ncol) == 0)
        return 0;
    // determina a cte através do simétrico n² + 1
    int cte = (nlin * nlin) + 1;

    // checa os valores simétricos
    // faz duas voltas, começa com [0][0] + [n-1][n-1] depois [0][1] + [n-1][n-2]... no loop interno
    // no externo vai para [1][0] + [n-2][n-1] depois [1][1] + [n-2][n-2]...

    for (int a = 0, b = nlin - 1; a < nlin; b--, a++)
    {
        for (int c = 0, d = ncol - 1; c < nlin; d--, c++)
        {
            if (matriz[a][c] + matriz[b][d] != cte)
                return 0;
        }
    }
    return 1;
}

int QuadradoMagicoBorda(int **matriz, int nlin, int ncol)
{
    if (nlin < 4 || ncol < 4)
        return 0; // Quadrado magico 2x2 ou menor
    if (QuadradoMagico(matriz, nlin, ncol) == 0)
        return 0;

    // Checa se a matriz interna eh magico
    int cte = 0;
    for (int i = 1; i < ncol - 1; i++) // guarda a soma dos elementos da primeira linha (constante)
    {
        cte += matriz[1][i];
    }

    // Checa a soma das linhas da matriz interna
    for (int i = 1; i < nlin - 1; i++)
    {
        int soma = 0;
        for (int j = 1; j < ncol - 1; j++)
        {
            soma += matriz[i][j];
        }

        if (soma != cte)
            return 0;
    }
    // Checa a soma das colunas da matriz interna
    for (int i = 1; i < ncol - 1; i++)
    {
        int soma = 0;
        for (int j = 1; j < nlin - 1; j++)
        {
            soma += matriz[j][i];
        }

        if (soma != cte)
            return 0;
    }
    // Checa diagonal primaria da matriz interna
    int soma = 0;
    for (int i = 1; i < nlin - 1; i++)
    {
        soma += matriz[i][i];
    }
    if (soma != cte)
        return 0;
    // Checa diagonal secundaria da matriz interna
    soma = 0;
    for (int i = 1, j = ncol - 2; i < nlin - 1; i++, j--)
    {
        soma += matriz[i][j];
    }
    if (soma != cte)
        return 0;

    return 1;
}

void FreeMatriz(int **matriz, int linhas)
{
    for (int i = 0; i < linhas; i++)
    {
        free(matriz[i]); // free cada linha
    }
    free(matriz); // free na matriz
}
int main()
{
    int nlin, ncol;
    printf("Entre com o numero de linhas: ");
    scanf("%d", &nlin);
    printf("Entre com o numero de colunas: ");
    scanf("%d", &ncol);
    // cria a matriz
    int **matriz = (int **)malloc(sizeof(int *) * nlin);
    for (int i = 0; i < nlin; i++)
    {
        matriz[i] = (int *)malloc(sizeof(int) * ncol); // cria as colunas para cada linha
    }
    // guarda cada entrada separada por enter
    printf("Entre com os valores da matriz: ");
    for (int i = 0; i < nlin; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }
    // PRINTS
    // declaração das caracteristicas
    int semi = SemiQuadradoMagico(matriz, nlin, ncol);
    int magic = QuadradoMagico(matriz, nlin, ncol);
    int ass = QuadradoMagicoAss(matriz, nlin, ncol);
    int borda = QuadradoMagicoBorda(matriz, nlin, ncol);
    // se não for quadrada, é comum
    if (nlin != ncol)
    {
        printf("Matriz Comum\n");
        return 0;
    }
    // Condiçoes para os prints
    if (borda == 1)
    {
        printf("Quadrado Magico Com Borda\n");
        return 0;
    }
    else if (ass == 1)
    {
        printf("Quadrado Magico Associativo\n");
        return 0;
    }
    else if (magic == 1)
    {
        printf("Quadrado Magico\n");
        return 0;
    }
    else if (semi == 1)
    {
        printf("Semi Quadrado Magico\n");
        return 0;
    }
    else
    {
        printf("Matriz Comum\n");
        return 0;
    }
    FreeMatriz(matriz, nlin);
    return 0;
}
