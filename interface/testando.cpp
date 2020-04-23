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
        if (!(stream >> teste))
            cout << "NADA";
        else for (int i = 0; i < teste.size(); i++) cout << toupper(teste[i]);
        cout << endl;

        cout << teste.back() << endl;
    }
    cout << "ACABOU" << endl;
    return 0;
}