// faz com que não seja necessário escrever "std::" antes das estruturas e algoritmos que estão no namespace std
#include <bits/stdc++.h>
 
int main() {
    
    int d, a, n;
    
    std::cin >> d;
    std::cin >> a;
    std::cin >> n;
    int dias = 32 - n;
    int dif = n - 11;

    // Limitamos o incremento a no máximo 4
    int incremento = (dif <= 4) * dif + (dif > 4) * 4;
    std::cout << (d*31) - ((n-1)*(a) - ;

    // deixa o cin/cout rápido. Se optar por printf/scanf, remova esta linha. Nunca misture as duas formas!
    std::ios_base::sync_with_stdio(0); std::cin.tie(0);
 
    return 0;
}