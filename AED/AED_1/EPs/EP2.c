//--------------------------------------------------------------
// NOME: Rafael Pioto Gomes
//       Rafael de Santana Lima
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// ######### ESCREVA SEU NROUSP AQUI
const char *nroUSP1()
{
    return ("16897842");
}

// ######### ESCREVA SEU NROUSP AQUI
const char *nroUSP2()
{
    return ("9797041");
}

// ######### ESCREVA O NRO DO SEU GRUPO AQUI
int grupo()
{
    return 1;
}

// no da arvore
typedef struct estr
{
    int chave;
    struct estr *esq;
    struct estr *dir;
} NO;

// no de lista ligada (caso queira usar alguma estrutura auxiliar)
typedef struct estrL
{
    int chave;
    struct estrL *prox;
} NOL;

int ContarAltura(NO *p)
{
    if (p)
    {
        int e;
        int d;
        e = ContarAltura(p->esq);
        d = ContarAltura(p->dir);
        if (e >= d)
        {
            return e + 1;
        }
        else
        {
            return d + 1;
        }
    }
    return 0;
}

// ferias na bahia
void ContarEle(NO *p, int **v, int i)
{
    if (p)
    {
        (*v)[i]++;
        ContarEle(p->esq, v, i + 1);
        ContarEle(p->dir, v, i + 1);
    }
}

void ListaFilhos(NO *p, int n, int mais, NOL **f, NOL **ant)
{
    if (p)
    {
        if (n > mais)
        {
            NOL *novo = (NOL *)malloc(sizeof(NOL));
            novo->chave = p->chave;
            novo->prox = NULL;
            if (*ant)
            {
                (*ant)->prox = novo;
            }
            else
            {
                (*f) = novo;
            }
            (*ant) = novo;
        }
        ListaFilhos(p->esq, n + 1, mais, f, ant);
        ListaFilhos(p->dir, n + 1, mais, f, ant);
    }
    return;
}

void inserir(NO **p, int ch)
{
    if (!(*p))
    {
        NO *novo = (NO *)malloc(sizeof(NO));
        novo->chave = ch;
        novo->dir = NULL;
        novo->esq = NULL;
        *p = novo;
        return;
    }
    NO *aux = *p;
    if (aux->chave > ch)
        inserir(&aux->esq, ch);
    if (aux->chave < ch)
        inserir(&aux->dir, ch);
}


void excluirNv(NO **raiz, NO *p, int n, int mais)
{
    if (p)
    {
        excluirNv(raiz, p->esq, n + 1, mais);
        excluirNv(raiz, p->dir, n + 1, mais);
        if (n >= mais)
        {
            if (mais == 1)
                (*raiz) = NULL;
            free(p);
        }
        if (n == mais - 1)
        {
            p->esq = NULL;
            p->dir = NULL;
        }
    }
    return;
}

//------------------------------------------
// O EP consiste em implementar esta funcao
//------------------------------------------
NO *RemoverNivelMaisExtenso(NO *raiz)
{
    // seu codigo ALI ó

    if (!raiz)
        return NULL;
    int n = ContarAltura(raiz);
    int *v = (int *)malloc(sizeof(int) * (n + 1));
    for (int i = 0; i <= n; i++)
    {
        v[i] = 0;
    }
    ContarEle(raiz, &v, 1);
    int maiorNv = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i] > v[maiorNv])
        {
            maiorNv = i;
        }
    }

    NOL *f = NULL;
    NOL *ant = NULL;
    ListaFilhos(raiz, 1, maiorNv, &f, &ant);
    excluirNv(&raiz, raiz, 1, maiorNv);
    while (f)
    {
        inserir(&raiz, f->chave);
        f = f->prox;
    }

}

//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
// mas nao entregue nada a partir deste ponto
//---------------------------------------------------------

// graphviz

void gera_dot_helper(NO *no)
{
    if (no == NULL)
    {
        return;
    }
    printf("  n%p [label=\"%d\"];\n", (void *)no, no->chave);
    if (no->esq != NULL)
    {
        printf("  n%p -> n%p;\n", (void *)no, (void *)no->esq);
        gera_dot_helper(no->esq);
    }
    if (no->dir != NULL)
    {
        printf("  n%p -> n%p;\n", (void *)no, (void *)no->dir);
        gera_dot_helper(no->dir);
    }
}

void exporta_graphviz(NO *raiz)
{
    printf("digraph ABB {\n");
    printf("  node [shape=circle, style=filled, color=\"#82E0AA\"];\n");
    printf("  edge [color=\"#5D6D7E\"];\n");
    if (raiz == NULL)
    {
        printf("  NULL [shape=plaintext];\n");
    }
    else
    {
        gera_dot_helper(raiz);
    }
    printf("}\n");
}
int main()
{
    NO *raiz = NULL;
    inserir(&raiz, 70);
    inserir(&raiz, 3);
    inserir(&raiz, 11);
    inserir(&raiz, 100);
    inserir(&raiz, 5);
    inserir(&raiz, 9);
    inserir(&raiz, 13);
    inserir(&raiz, 2);
    inserir(&raiz, 40);
    inserir(&raiz, 1999);
    inserir(&raiz, 511);
    inserir(&raiz, 92312);
    inserir(&raiz, 18);
    inserir(&raiz, 20);
    inserir(&raiz, 84);
    RemoverNivelMaisExtenso(raiz);

    exporta_graphviz(raiz);

    // serao realizadas chamadas como esta:
    // NO* resp = RemoverNivelMaisExtenso(raiz);
}

// por favor nao inclua nenhum código abaixo da função main()