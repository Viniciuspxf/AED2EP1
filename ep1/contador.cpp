#include <bits/stdc++.h>
using namespace std;

int main() {
    double soma = 0, atual;
    int quantidade = 0;
    string linha, nada;
    while (getline(cin, linha)) {
        stringstream stream(linha);
        if (getline(cin, linha)) {
            quantidade++;
            stream >> nada;
            stream >> nada;
            stream >> nada;
            stream >> atual;
            soma += atual;
        }
    }
    cout << "soma: " << soma << endl;
    cout << "quantidade: " << quantidade << endl;
    cout << "media: " << soma/quantidade << endl << endl;
    return 0;
}