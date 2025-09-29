#include <stdio.h>
#include <stdlib.h>




int contagem( int *valores, int n, int x)
{
    int cont = 0;
    for (int i = 0; i < n; i++) {
        if (valores[i] == x)
            cont++;
    }
    return cont;
}


int main() {
  int* x = (int*) malloc(sizeof(int)*10);
  x[0] = 3;
  x[1] = 4;
  x[2] = 5;
  x[3] = -1;
  x[4] = 7;
  x[5] = 3;
  x[6] = 4;
  x[7] = 3;
  x[8] = -1;
  x[9] = 3;
  
  printf("Resultado: %i\n", contagem(x, 10, 3));

  free(x);

  return 0;
}