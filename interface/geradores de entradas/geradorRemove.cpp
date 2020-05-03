#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(555);
    vector<string> palavras, corrente;
    string palavra;
    int i, j;
    while (cin >> palavra) {
        cin >> palavra;
        palavras.push_back(palavra);
        corrente.push_back(palavra);
    }

    for (i = 0; i < palavras.size(); i++) {
        cout << "rankST "<< palavras[i] << endl;
    }

    for (i = 0; i < 1000; i++) {
        j = rand()%corrente.size();
        cout << "deleteST " << corrente[j] << endl;
    }

    for (i = 0; i < palavras.size(); i++) {
        cout << "rankST "<< palavras[i] << endl;
    }
}