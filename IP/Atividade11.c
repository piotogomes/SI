#include <stdio.h>
#include <stdlib.h>


typedef struct aux{
  float baseMenor;
  float baseMaior;
  float altura;
} TRAPEZIO;


float areaTrapezio1(TRAPEZIO t1) {

  return ((t1.baseMaior + t1.baseMenor)*t1.altura/2);

}

float areaTrapezio2(TRAPEZIO* r1) {

  return ((r1->baseMaior + r1->baseMenor)*r1->altura/2);

}


int main() {
  TRAPEZIO* trap = (TRAPEZIO*) calloc(1, sizeof(TRAPEZIO));
  printf("Valor base menor: ");
  scanf("%f", &trap->baseMenor);  
  printf("Valor base maior: ");
  scanf("%f", &trap->baseMaior);
  printf("Valor altura: ");
  scanf("%f", &trap->altura);

  printf("Area do trapezio: %.2f\n",areaTrapezio2(trap));
  
  return 0;
}


/* SAIDA
Area do trapezio: 8.50
Area do trapezio: 8.50
*/