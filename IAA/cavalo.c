#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int hor[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int ver[8] = {2, 1, -1, -2, -2, -1, 1, 2};


void tenta(int i, int d, int x, int y, bool *q, int **tab) {
    bool q1;
    int k = -1;
    int u;
    int v;
    do {
        ++k;
        q1 = false;
        u = x + ver[k];
        v = y + hor[k];
        // printf("k ");
        if(u < d && u >= 0 && v < d && v >= 0) {
            if(tab[u][v] == 0) {
                tab[u][v] = i;
                if(i < d*d) {
                    tenta(i+1, d, u, v, &q1, tab);
                    if(!q1) {
                        tab[u][v] = 0;
                    }
                    
                }
                else q1 = true;
            }
        }
    } while(!(q1 || k == 7));
    *q = q1;
    return;
}




int main() {
    
    bool q;
    int d;
    scanf("%d", &d);
    
    int** tab = (int**) malloc(sizeof(int*)*d);
    for(int i = 0; i < d; i++) {
        tab[i] = (int*) malloc(sizeof(int)*d);
    }
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            tab[i][j] = 0;
        }
    }
    int x0, y0;
    scanf("%d %d", &x0, &y0);
    tenta(2, d, x0, y0, &q, tab);
    if(!q) {
        printf("sem solu\n");
        return 0;
    }
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            printf("[%d] ", tab[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}