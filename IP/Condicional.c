#include <stdio.h>

float aliquota_sw();
float aliquota_if();

int main() {
int x,y,z,salario;

printf("salario");

// scanf("%f %f %f",&x,&y,&z);

// Inclua seu código.

scanf("%i", &salario);
float aliq = aliquota_sw(salario);
printf("aliquota switch: %.2f\n", aliq);
aliq = aliquota_if(salario);
printf("aliquota if else: %.2f\n", aliq);

printf("%b", 1929);

}


float aliquota_sw(int salario) {

    float ali = 0.0;
    switch (salario)
    {
    case 1902 ... 2826:
        ali = 7.5;
        break;
    case 2827 ... 3751:
        ali = 15;
        break;
    case 3752 ... 4664:
        ali = 22.5;
        break;
    case 4665 ... 100000:
        ali = 27.5;
        break;
    default:
        ali = 0.0;
        break;
    }


    return ali;
}

float aliquota_if(int salario){
    float ali = 0;


    if (salario <= 1902) ali = 0.0;
    else if (salario > 1902 && salario <= 2826) ali = 7.5;
    else if (salario > 2827 && salario <= 3751) ali = 15;
    else if (salario > 3752 && salario <= 4665) ali = 22.5;
    else if (salario > 4666) ali = 27.5;

    return ali;
}

