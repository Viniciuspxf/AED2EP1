#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    string caracteres;
    while (getline(cin, caracteres)) {
        string teste;
        int teste2;
        stringstream stream(caracteres);
        if (!(stream >> teste2))
            cout << "NADA" << endl;
        else cout << teste2 << endl;
    }
    cout << "ACABOU" << endl;
    return 0;
}