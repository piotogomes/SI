#include <stdio.h>

int main() {
    // Write C code here
    int a, b, i;
    printf("Entre com um numero positivo:");
    scanf("%i",&a);
    printf("%i por ser dividido por: ", a);
    
    for(i=2; i <= 11; ++i){
        switch(i){
            case 2:
                !(a%i) ? printf("%d ", i) : printf(""); 
            break;
            case 3:
            break;
            case 4:
            break;
            case 5:
            break;
            case 6:
            break;
            case 9:
            break;
            case 10:
            break;
            case 11:
            break;
        }
    }
    printf("\n");
    return 0;
}