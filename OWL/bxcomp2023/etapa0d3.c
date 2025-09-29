#include <stdio.h>



void main() {

    int t;
    scanf("%d", &t);

    for(int i = 0; i < t; i++) {
        int partidas;
        scanf("%d", &partidas);
        int jog1;
        int jog2;
        int total2 = 0;
        int total1 = 0;
        for(int j = 0; j < partidas; j++) {
            scanf("%d", &jog1);
            scanf("%d", &jog2);
            if(jog1 > jog2) {
                printf("%d-1 ", jog1);
                total1++;
            }
            else if(jog1 < jog2) {
                printf("%d-2 ", jog2);
                total2++;
            }
            else {
                printf("%d-Empate ", jog1);   
            }        
        }
        if(total1 > total2) {
            printf("Resultado: 1\n");
        }
        else if(total1 < total2) {
            printf("Resultado: 2\n");
        }
        else {
            printf("Resultado: Empate\n");
        }

    }

    return;
}