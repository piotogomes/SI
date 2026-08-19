#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define V 100

void inicializar(int m[V][V])
{
    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            m[i][j] = 0;
        }
    }
}

// busca em prof, zerar flags
void prof(int m[V][V], int i, int flags[V])
{
    flags[i] = 1;
    for (int j = 1; j <= V; j++)
    {
        if (m[i][j] == 1)
        {
            if (flags[j] == 0)
            {
                prof(m, j, flags);
            }
        }
    }
    flags[i] = 2;
}

void larg(int m[V][V], int i, int flags[V]) {
    
}