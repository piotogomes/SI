#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool ocupado(int u, int v, int d, int** tab){
    for(int i = 0; i < d; i++){
        if(tab[i][v] == 1) return true;
        if(tab[u][i] == 1) return true;
        if(u+i < d && v+i < d) if(tab[u+i][v+i] == 1) return true;
        if(u-i >= 0 && v+i < d) if(tab[u-i][v+i] == 1) return true;
        if(u+i < d && v-i >= 0) if(tab[u+i][v-i] == 1) return true;
        if(u-i >= 0 && v-i >= 0) if(tab[u-i][v-i] == 1) return true;
	}
    return false;
}



void tenta(int d, int j, int y, bool *q, int **tab)
{
    bool q1;
    if(j == d) {
        q1 = true;
        *q = q1;
        return;
    }
    if(j == y) {
        tenta(d, j + 1, y, &q1, tab);
    }
    else{
        for(int i = 0; i < d; i++) {

            if(!ocupado(i, j, d, tab)) {
                tab[i][j] = 1;
                tenta(d, j + 1, y, &q1, tab);
                if(q1) break;
                else tab[i][j] = 0;
            }
        }

    }
    *q = q1;
    return;
}

int main()
{

    bool q;
    int d;
    scanf("%d", &d);

    int **tab = (int **)malloc(sizeof(int *) * d);
    for (int i = 0; i < d; i++)
    {
        tab[i] = (int *)malloc(sizeof(int) * d);
    }
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            tab[i][j] = 0;
        }
    }
    int x0, y0;
    scanf("%d %d", &x0, &y0);
    tab[x0][y0] = 1;
    tenta(d, 0, y0, &q, tab);
    if (!q)
    {
        printf("sem solu\n");
        return 0;
    }
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            printf("[%d] ", tab[i][j]);
        }
        printf("\n");
    }

    return 0;
}