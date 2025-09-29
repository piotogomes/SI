#include <stdio.h>
#include <math.h>

int testeFib(int n) {
    double raiz;
    raiz = sqrt(5*n*n + 4);
    if(((int) raiz * (int) raiz) == 5*n*n + 4) return 1;
    raiz = sqrt(5*n*n - 4);
    if(((int) raiz * (int) raiz) == 5*n*n - 4) return 1;
    return 0;
}

void solve(){
    int i;
    scanf("%d", &i);
    int pet;
    int dino;
    int pontoPet = 0;
    int pontoDino = 0;
    while (i > 0) {

        scanf("%d", &pet);
        scanf("%d", &dino);

        if(testeFib(pet)) {
            if(testeFib(dino) == 0 && dino % 2 == 0) pontoDino++;
            if(testeFib(dino) == 0 && dino % 2 != 0) pontoPet++;
        }
        if(testeFib(pet) == 0 && pet % 2 == 0) {
            if(testeFib(dino) == 0 && dino % 2 != 0) pontoDino++;
            if(testeFib(dino)) pontoPet++;
        }
        if(testeFib(pet) == 0 && pet % 2 != 0) {
            if(testeFib(dino)) pontoDino++;
            if(testeFib(dino) == 0 && dino % 2 == 0) pontoPet++;
        }
        i--;
    }
    if(pontoPet > pontoDino) printf("A CORUJA VOLTOU A PIAAAAAR!!!!!\n");
    else if(pontoDino > pontoPet) printf("NOOO, ACHO QUE OS DINOSSAUROS VAO TER CORUJA AO FORNO HOJE NA JANTA\n");
    else printf("Precisamos marcar uma revanche...\n");
}

int main(){
    int n;
    scanf("%i", &n);

    while(n--){
        solve();
    }
    return 0;
}