#include <stdio.h>
#include <string.h>




void main() {

    char cod[4];
    do {

        scanf("%s", cod);
        int count = 0;
        int len = 0;
        if(strcmp("QTH", cod) == 0) {
            char msg[100];
            scanf("%s", msg);
            for(int i = 0; msg[i] != '\0'; i++) {
                if(msg[i] == '*' || msg[i] == '@' || msg[i] == '&' || msg[i] == '!') {
                    count++;
                }
                len++;
            }
            if(count > len / 2) {
                printf("Base T, estou com muito QRT na mensagem, poderia reenviar ?\n");
            }
            else {
                printf("Imperatriz, o pouso sera na zona %s\n", msg);
            }
        }

    }   while(strcmp("QAR", cod) != 0);





    return;
}