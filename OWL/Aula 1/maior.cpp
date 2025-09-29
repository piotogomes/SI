// faz com que não seja necessário escrever "std::" antes das estruturas e algoritmos que estão no namespace std
#include <bits/stdc++.h>
using namespace std;
 
int main() {
    
    int n, m;
    
    std::cin >> n;
    std::cin >> m;
    std::cout << (m - n) + m;

    // deixa o cin/cout rápido. Se optar por printf/scanf, remova esta linha. Nunca misture as duas formas!
    ios_base::sync_with_stdio(0); cin.tie(0);
 
    return 0;
}