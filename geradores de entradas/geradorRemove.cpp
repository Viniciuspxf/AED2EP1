#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(555);
    vector<string> palavras, corrente;
    string linha, chave;
    int i, j, k, num;
    while (getline(cin, linha)) {
        stringstream stream(linha);
        stream >> chave;
        if (chave == ">>>") {
            stream >> chave;
            stream >> chave;
            stream >> chave;
            if (stream >> chave) {
                palavras.push_back(chave);
                corrente.push_back(chave);
            }
        }
    }
   

    for (i = 0; i < palavras.size(); i++) {
        cout << "getST "<< palavras[i] << endl;
    }

    for (k = 0; k < 8; k++){
        if (k < 2) num = 1000;
        else num = 500;
        for (i = 0; i < num; i++) {
            j = rand()%corrente.size();
            cout << "deleteST " << corrente[j] << endl;
        }

        for (i = 0; i < palavras.size(); i++) {
            cout << "getST "<< palavras[i] << endl;
        }
    }
}