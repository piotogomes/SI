#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define stdin stdin


void converter(int n, int b) {
    if (n == 0) return;
    converter(n / b, b);
    int result = n % b;
    if (n % b >= 10) {
        result += 55;
        printf("%c", result);
    }
    else {
        printf("%d", result);
    }
}
int main() {
    char n[50], b[50];
    //fgets(n, sizeof(n), stdin);

    printf("%d", (int)n);
    n[strcspn(n, "\n")] = 0;
    // converter((int)n, (int)b);
    printf("\n");
    return 0;
    }

