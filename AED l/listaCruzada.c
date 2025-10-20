#include <stdio.h>
#include "listas.h"

void LC_inicializar(ListaCr *matriz)
{
    for (int i = 0; i < MAX - 1; i++)
    {
        matriz->lin[i] = NULL;
        matriz->col[i] = NULL;
    }
}

NOListaCr *busca_LC(int i, int j, ListaCr *matriz, NOListaCr **esq, NOListaCr **acima)
{

    NOListaCr *atual = matriz->lin[i];
    *esq = NULL;
    *acima = NULL;
    while (atual)
    {
        if (atual->c >= j)
            break;
        *esq = atual;
        atual = atual->proxCol;
    }

    atual = matriz->col[i];

    while (atual)
    {
        if (atual->l >= i)
            break;
        *acima = atual;
        atual = atual->proxLin;
    }
    if (atual && (atual->l != i || atual->c != j))
        return NULL;
    return atual;
}

void LC_inserir(int i, int j, int ch, ListaCr *matriz)
{
    NOListaCr *esq;
    NOListaCr *acima;
    NOListaCr *atual = busca_LC(i, j, matriz, &esq, &acima);
    if (ch == 0 && !atual)
        return;
    if (ch != 0 && atual)
    {
        atual->chave = ch;
        return;
    }
    if (ch == 0 && atual)
    {

        if (esq)
            esq->proxCol = atual->proxCol;
        else
            matriz->lin[i] = atual->proxCol;
        if (acima)
            acima->proxLin = atual->proxLin;
        else
            matriz->col[j] = atual->proxLin;
        free(atual);
        return;
    }
    if (ch != 0 && !atual)
    {
        NOListaCr *novo = (NOListaCr *)malloc(sizeof(NOListaCr));
        novo->chave = ch;
        novo->c = j;
        novo->l = i;

        if (esq)
        {
            novo->proxCol = esq->proxCol;
            esq->proxCol = novo;
        }
        else
        {
            novo->proxCol = matriz->lin[i];
            matriz->lin[i] = novo;
        }
        if (acima)
        {
            novo->proxLin = acima->proxLin;
            acima->proxLin = novo;
        }
        else
        {
            novo->proxLin = matriz->lin[j];
            matriz->lin[j] = novo;
        }
        return;
    }
}

// quantos zeros existem na linha i

int contarZeroLin(int i, ListaCr *matriz)
{
    NOListaCr *atual = matriz->lin[i];
    int cont = MAX;
    while (atual)
    {
        cont--;
        atual = atual->proxCol;
    }
    return cont;
}

void LC_exibir(ListaCr *matriz)
{
    for (int i = 0; i < MAX - 1; i++)
    {
        NOListaCr *atual = matriz->lin[i];
        while (atual)
        {
            printf("%d", atual->chave);
            atual = atual->proxCol;
        }
    }
}

void exibir_LC_zeros(ListaCr *matriz)
{
    for (int i = 0; i < MAX; i++)
    {
        NOListaCr *atual = matriz->lin[i];
        if (!atual)
        {
            for (int j = 0; j < MAX - 1; j++)
            {
                printf("0 ");
            }
        }
        else
        {
            int cont = 0;
            while (atual)
            {
                for (int j = cont; j < atual->c; j++)
                {
                    printf("0 ");
                    cont++;
                }
                printf("%d ", atual->chave);
                if (atual->proxCol)
                {
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
}

void exibirDiag(ListaCr *matriz)
{
    for (int i = 0; i < MAX; i++)
    {
        NOListaCr *atual = matriz->lin[i];
        while (atual)
        {
            if (atual->c == atual->l)
            {
                printf("%d", atual->chave);
                break;
            }
            if (atual->c > i)
            {
                printf("0");
                break;
            }
            atual = atual->proxCol;
        }
        if (!atual)
            printf("0");
    }
}

void zerarCol(int j, ListaCr *matriz)
{

    // percorrer as linhas
    NOListaCr *atual;
    NOListaCr *ant = NULL;
    for (int i = 0; i < MAX; i++)
    {
        atual = matriz->lin[i];
        while (atual)
        {
            if (atual->c == j)
            {
                if (ant)
                    ant->proxCol = atual->proxCol;
                else
                    matriz->lin[i] = atual->proxCol;
                free(atual);
                break;
            }
            if (atual->c > j)
                break;
            ant = atual;
            atual = atual->proxCol;
        }
    }
    matriz->col[j] = NULL;
}
// preencher a linha i com valor k
void criarLinhaCte(int i, int k, ListaCr *matriz)
{
    for (int j = 0; j < MAX; j++)
    {
        inserir_LC(i, j, k, matriz);
    }
}

// Para todas ch != 0, incrementar o valor do elemento na coluna seguinte, se for > 0
void somarProx(ListaCr *matriz, int k)
{
    for (int i = 0; i < MAX; i++)
    {
        NOListaCr *atual = matriz->lin[i];
        while (atual)
        {
            if (atual->proxCol && atual->chave == k && atual->proxCol->c == atual->c + 1)
            {
                atual->proxCol->chave++;
            }
        }
        atual = atual->proxCol;
    }
}

void zerarDiag(ListaCr *matriz)
{
    NOListaCr *esq;
    NOListaCr *acima;
    for (int i = 0; i < MAX; i++)
    {
        NOListaCr *atual = matriz->lin[i];
        while (atual)
        {
            if (atual->c == atual->l)
            {
                if (esq)
                    esq->proxCol = atual->proxCol;
                else
                    matriz->lin[i] = atual->proxCol;
                if (acima)
                    acima->proxLin = atual->proxLin;
                else
                    matriz->col[i] = atual->proxLin;
                free(atual);
                return;
            }
            atual = atual->proxCol;
        }
        if (!atual)
            printf("0");
    }
}

// verificar se duas listas cruzadas são identicas

int LC_iguais(ListaCr *matriz1, ListaCr *matriz2)
{
    for (int i = 0; i < MAX; i++)
    {
        NOListaCr *atual1 = matriz1->lin[i];
        NOListaCr *atual2 = matriz2->lin[i];
        while (atual1 && atual2)
        {
            if (atual1->chave != atual2->chave)
            {
                return 0;
            }
        }
        atual1 = atual1->proxCol;
        atual2 = atual2->proxCol;
    }
    return 1;
}

// lista cruzada e matriz esparsa identica

int LC_ME_iguais(MatrizEsp *matriz1, ListaCr *matriz2)
{
    NOMatrizEsp *NO_ME = matriz1->ini;
    NOListaCr *NO_LC;
    for (int i = 0; i < MAX; i++)
    {
        NO_LC = matriz2->lin[i];
        while (NO_LC)
        {
            if (!NO_ME)
                return false;
            if ((NO_LC->chave != NO_ME->chave) || NO_LC->l != NO_ME->linha || NO_LC->c != NO_ME->coluna)
                return false;
            NO_LC = NO_LC->proxCol;
            NO_ME = NO_ME->prox;
        }
    }
    if (NO_ME)
        return false;
    return true;
}