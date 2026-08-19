#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define V 100

typedef struct s
{
    int adj;
    struct s *prox;
    int cia; // exemplo de usar sempre a mesma companhia nos voos (aresta)
} NO;

typedef struct
{
    NO *inicio;
    int flag;   // flags para a busca
    bool visto; // exemplo de viajar para cidades que contenham visto, e uma busca que retorna uma lista para poder viajar
    int cap; // exemplo de achar as salas conectadas com capacidade >= x
    int tipo; // 1 = posto (exemplo busca largura) 
    int dist; // para a busca em largura no exemplo de achar a distancia

} Vertice;

void inicializar(Vertice *g)
{
    for (int i = 1; i <= V; i++)
    {
        g[i].inicio = NULL;
        g[i].flag = 0; // para a busca, 0 = n descoberto, 1 = descoberto, 2 = concluido
    }
}

void zerarFlag(Vertice *g)
{
    for (int i = 1; i <= V; i++)
    {
        g[i].flag = 0; // para a busca, 0 = n descoberto, 1 = descoberto, 2 = concluido
    }
}

bool existeAresta(Vertice *g, int v1, int v2, NO **ant)

{
    *ant = NULL;
    NO *p = g[v1].inicio;
    while (p)
    {
        if (p->adj == v2)
            return true;
        p = p->prox;
    }
    return false;
}

bool insereAresta(Vertice *g, int v1, int v2)
{
    NO *ant;
    if (existeAresta(g, v1, v2, &ant))
        return false;
    NO *novo = (NO *)malloc(sizeof(NO));
    novo->adj = v2;
    novo->prox = g[v1].inicio;
    g[v1].inicio = novo;
    return true;
}

bool ArestasEmG1(Vertice *g1, Vertice *g2)
{
    NO *ant;
    for (int i = 1; i <= V; i++)
    {
        NO *p = g2[i].inicio;
        while (p)
        {
            if (!existeAresta(g1, i, p->adj, &ant))
                return false;
            p = p->prox;
        }
    }
    return true;
}

Vertice *copia(Vertice *g)
{
    Vertice *resp = (Vertice *)malloc((V + 1) * sizeof(Vertice));
    inicializar(resp);
    for (int i = 1; i <= V; i++)
    {
        NO *p = g[i].inicio;
        while (p)
        {
            NO *novo = (NO *)malloc(sizeof(NO));
            novo->adj = p->adj;          // = i (transposta)
            novo->prox = resp[i].inicio; // = resp[p->adj].inicio (transposta)
            resp[i].inicio = novo;       // resp[p->adj].inicio = novo
            p = p->prox;
        }
    }
    return resp;
}

// BUSCA EM PROFUNDIDADE

void zerarFlag(Vertice *g)
{
    for (int i = 1; i <= V; i++)
    {
        g[i].flag = 0; // para a busca, 0 = n descoberto, 1 = descoberto, 2 = concluido
    }
}

// busca em profundidade

void prof(Vertice *g, int i)
{
    g[i].flag = 1;
    NO *p = g[i].inicio;
    while (p)
    {
        if (g[p->adj].flag == 0)
        {
            prof(g, p->adj);
        }
        p = p->prox;
    }
    g[i].flag = 2;
}

// 1. existe caminho entre i e j, resp = false

void existeCaminho(Vertice *g, int i, int j, bool *resp)
{
    g[i].flag = 1;
    if (i == j)
    {
        *resp = true;
        return;
    }
    NO *p = g[i].inicio;
    while (p)
    {
        if (g[p->adj].flag == 0 && !(*resp))
        {
            existeCaminho(g, p->adj, j, resp);
        }
        p = p->prox;
    }
    g[i].flag = 2;
}

// 2. exibe a areta q fecha o ciclo

void exibirCiclo(Vertice *g, int i)
{
    g[i].flag = 1;
    NO *p = g[i].inicio;
    while (p)
    {
        if (g[p->adj].flag == 1 && i != p->adj)
        {
            printf("Aresta %d %d", i, p->adj);
        }
        if (g[p->adj].flag == 0)
        {
            exibirCiclo(g, p->adj);
        }
        p = p->prox;
    }
    g[i].flag = 2;
}

// exemplo das viagens (campo visto nos vertices)
void ListaPaisesSemVisto(Vertice *g, int i, NO **resp)
{

    g[i].flag = 1;
    NO *p = g[i].inicio;
    while (p)
    {
        if (g[p->adj].flag == 0)
        {
            ListaPaisesSemVisto(g, p->adj, resp);
        }
        p = p->prox;
    }
    g[i].flag = 2;
    if (g[i].visto)
    {
        NO *novo = (NO *)malloc(sizeof(NO));
        novo->adj = i;
        novo->prox = *resp;
        *resp = novo;
    }
}

// exemplo das viagens pela mesma companhia X (campo cia nas arestas)

void verificarABporCia(Vertice *g, int a, int b, int cia, bool *achou)
{
    if (a == b)
    {
        *achou = true;
        return;
    }
    g[a].flag = 1;
    NO *p = g[a].inicio;
    while (p)
    {
        if (g[p->adj].flag == 0 && p->cia == cia)
        {
            verificarABporCia(g, p->adj, b, cia, achou);
        }
        if (*achou)
            return;
        p = p->prox;
    }
    g[a].flag = 2;
}

// converter grafo matriz em lista de adj

void converterMatrizEmList(int m[V][V], Vertice *g) // vertice g ja inicializado e vazio
{
    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            if (m[i][j] == 1)
            {
                insereAresta(g, i, j);
            }
        }
    }
}

// verificar se ha caminho de A até B passando por X (considerando g com flag zerada)

bool verificarAXB(Vertice *g, int a, int b, int x)
{
    bool *AX;
    bool *BX;
    *AX = false;
    *BX = false;
    existeCaminho(g, a, x, AX);
    if (*AX)
    {
        zerarFlag(g);
        existeCaminho(g, x, b, BX);
    }
    return *BX;
}

// exibir até N salas com capacidade >=x alcançaveis a partir de i

void salasGrandesConectadas(Vertice *g, int i, int tam, int* N)
{
    g[i].flag = 1;
    NO *p = g[i].inicio;
    while (p)
    {
        if (g[p->adj].flag == 0)
        {
            salasGrandesConectadas(g, p->adj, tam, N);
            if(*N == 0) return;
        }
        p = p->prox;
    }
    if(g[i].cap >= tam) {
        printf("%d ", i);
        *N -= 1;
    }
    g[i].flag = 2;
}


int main()
{

    return 0;
}
