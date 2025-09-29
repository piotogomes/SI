#include <stdio.h>



void main() {

    int t;
    scanf("%d", &t);

    for(int i = 0; i < t; i++) {
        int pos = 0;
        int v[10];
        for(int j = 0; j < 10; j++) {
            scanf("%d", &v[j]);
            if (v[j] == 1) {
                pos = j;
            }
            if(v[j] == 2){
                if((10 - j) <= j - pos - 1) {
                    printf("Explorador do espaço para base alpha, conseguimos passar pela chuva de meteoros!");
                    break;
                }
                else {
                    printf("Nu, vou tascar um beijo numa pedra do espaço se eu entrar ai, paia.");
                    break;
                }
            }
        
        }
    }

    return;
}