#include <stdio.h>
#include <stdlib.h>

typedef struct s
{
    long long soma;
    long linha;
} SomaLinha;


static void msort(SomaLinha *a, SomaLinha *t, int l, int r){
    if(r - l < 2) return;
    int m = (l + r) / 2;
    msort(a, t, l, m);
    msort(a, t, m, r);
    int i = l, j = m, k = l;
    while(i < m || j < r)
        t[k++] = (j >= r || (i < m && a[i].soma <= a[j].soma)) ? a[i++] : a[j++];
    for(i = l; i < r; ++i) a[i] = t[i];
}

void mergesort(SomaLinha *a, int n){
    if(n < 2) return;
    SomaLinha *t = malloc(n * sizeof *t);
    if(!t) { perror("malloc"); return; }
    msort(a, t, 0, n);
    free(t);
}

long long score(long long v[], long len)
{
    long long sum = 0;
    long j = len;
    for (long i = 0; i < len; i++)
    {
        sum += v[i] * j;
        j--;
    }
    return sum;
}

void solve()
{
    long nVetor;
    long len;
    scanf("%ld %ld", &nVetor, &len);
    SomaLinha somas[nVetor];
    long **dados = (long **)malloc(sizeof(long *) * nVetor);
    for (long i = 0; i < nVetor; i++)
    {
        dados[i] = (long *)malloc(sizeof(long) * len);
    }
    
    
    long long concatenado[nVetor * len];
    
    for (long i = 0, soma; i < nVetor; i++)
    {
        soma = 0;
        for (long j = 0; j < len; j++)
        {
            scanf("%ld", &dados[i][j]);
            soma += dados[i][j];
        }
        somas[i].soma = soma;
        somas[i].linha = i;

    }
    mergesort(somas, nVetor);

    long lin = nVetor - 1;
    for(long i = 0; i < len*nVetor;) {
        for(long j = 0; j < len; j++) {
            concatenado[i++] = dados[somas[lin].linha][j];
        }
        lin--;
    }
    for(long i = 0; i < nVetor; i++) {
        free(dados[i]);
    }
    free(dados);
    printf("%lld\n", score(concatenado, nVetor * len));
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