#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// ######### ESCREVA o nro USP DO PRIMEIRO INTEGRANTE AQUI
char *nroUSP1()
{
    return ("16897842");
}

// ######### nro USP DO SEGUNDO INTEGRANTE (OU DEIXE COMO ESTA)
char *nroUSP2()
{
    return ("9797041");
}

// ######### NRO DO SEU GRUPO CONFORME PLANILHA
int grupo()
{
    return 1;
}

// elemento da lista
typedef struct estr
{
    int chave;
    struct estr *prox;
} NO;

// lista
typedef struct
{
    NO *inicio;
} LISTA;

// funcao principal
void separar(LISTA *l1, LISTA *l2);

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------

NO *pontoComum(LISTA *l1, LISTA *l2)
{
    NO *atual1 = l1->inicio;
    NO *atual2 = l2->inicio;

    for (; atual1; atual1 = atual1->prox)
    {
        for (atual2 = l2->inicio; atual2; atual2 = atual2->prox)
        {
            if (atual2 == atual1)
                return atual1;
        }
    }

    // while(atual2) {
    //     while((atual1 != atual2) && atual1) {
    //         atual1 = atual1->prox;
    //         if(atual1 && (atual2 == atual1)) {
    //             return atual2;
    //         }
    //     }
    //     atual1 = l1->inicio;
    //     atual2 = atual2->prox;
    // }
}
void separar(LISTA *l1, LISTA *l2)
{

    // seu codigo AQUI
    NO *atual = l1->inicio;
    NO *p = pontoComum(l1, l2);
    NO *inicio1 = l1->inicio;
    l1->inicio = p->prox;
    printf("p %d\n", p->chave);

    // ponto em comum acontece no inicio da l1
    if (atual == p)
    {
        p->prox = NULL;
        return;
    }

    while (atual)
    {
        // resetando o atual para o comeco da l1
        atual = inicio1;
        // loop até o ponto em comum
        while (atual->prox != p)
        {
            atual = atual->prox;
        }
        // ligando a l2 no ultimo elemento de l1 antes do ponto em comum
        p->prox = atual;
        p = atual;
        // encerra l2 no primeiro elemento da l1
        if (atual == inicio1)
        {
            p->prox = NULL;
            break;
        }
    }
    return;
}

// por favor nao inclua nenhum codigo a ser entregue abaixo deste ponto

NO *busca(LISTA *l, int ch)
{
    NO *atual = l->inicio;
    while (atual->chave != ch)
    {
        atual = atual->prox;
        if (atual == NULL)
        {
            return NULL;
        }
    }
    return atual;
}
int inserir(LISTA *l, int ch)
{
    NO *atual = l->inicio;
    NO *novo = (NO *)malloc(sizeof(NO));
    novo->chave = ch;
    novo->prox = NULL;
    if (l->inicio == NULL)
    {
        l->inicio = novo;
        return 1;
    }
    while (atual->prox != NULL)
    {
        atual = atual->prox;
    }
    atual->prox = novo;
    return 1;
}
void exibir(LISTA *l)
{
    NO *atual = l->inicio;
    while (atual != NULL)
    {
        printf("%d ", atual->chave);
        atual = atual->prox;
    }
    printf("\n");
}

void ligarListas(LISTA *l1, LISTA *l2, int ch)
{
    NO *pontoDeLig = busca(l1, ch);
    NO *atual = l2->inicio;
    if (l2->inicio == NULL)
    {
        l2->inicio = l1->inicio;
        return;
    }
    while (atual->prox != NULL)
    {
        atual = atual->prox;
    }
    atual->prox = pontoDeLig;
    return;
}
//----------------------------------------------------------------
// use main() apenas para fazer chamadas de teste ao seu programa
//----------------------------------------------------------------
int main()
{

    LISTA *l1 = (LISTA *)malloc(sizeof(LISTA));
    LISTA *l2 = (LISTA *)malloc(sizeof(LISTA));
    l1->inicio = NULL;
    l2->inicio = NULL;

    // aqui vc pode inserir elementos de teste nas listas l1 e l2

    for (int i = 1; i < 5; i++)
    {
        inserir(l1, i);
    }
    for (int i = 5; i < 8; i++)
    {
        inserir(l2, i);
    }

    ligarListas(l1, l2, 4);
    // l2->inicio = l1->inicio;
    printf("Lista 1: ");
    exibir(l1);
    printf("Lista 2: ");
    exibir(l2);
    // o EP sera testado com chamadas deste tipo
    separar(l1, l2);
    printf("Lista 1: ");
    exibir(l1);
    printf("Lista 2: ");
    exibir(l2);
}
