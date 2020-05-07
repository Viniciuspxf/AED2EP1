#include <bits/stdc++.h>
using namespace std;

int main() {
    string chave, linha, comando;
    int n, i;
    comando = "deleteST ";
    while (getline(cin, linha)) {
        stringstream stream(linha);
        stream >> chave;
        if (chave == ">>>") {
            stream >> chave;
            stream >> chave;
            stream >> chave;
            if (stream >> chave) {
                cout << comando << chave << endl;
            }
        }
    }
    
    return 0;
}