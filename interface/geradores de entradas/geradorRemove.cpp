#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(555);
    vector<string> palavras, corrente;
    string palavra;
    int i, j, k, num;
    while (cin >> palavra) {
        cin >> palavra;
        cin >> palavra;
        cin >> palavra;
        cin >> palavra;
        palavras.push_back(palavra);
        corrente.push_back(palavra);
    }

    for (i = 0; i < palavras.size(); i++) {
        cout << "getST "<< palavras[i] << endl;
    }

    for (k = 0; k < 50; k++){
        if (k < 2) num = 30;
        else num = 25;
        for (i = 0; i < num; i++) {
            j = rand()%corrente.size();
            cout << "deleteST " << corrente[j] << endl;
        }

        for (i = 0; i < palavras.size(); i++) {
            cout << "getST "<< palavras[i] << endl;
        }
    }
}