#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    
    string nome1, nome2, linha1, linha2;

    ifstream arquivo1, arquivo2;

    cin >> nome1 >> nome2;
    arquivo1.open(nome1);
    arquivo2.open(nome2);

    int i = 0;

    while (getline(arquivo1, linha1) && getline(arquivo2, linha2)) {
        if (linha1 != linha2) {
            cout << "linha " << i << endl;
            cout << "linha do arquivo 1: " << linha1 << endl;
            cout << "linha do arquivo 2: " << linha2 << endl;
        }

        i++;
    }

    arquivo1.close();
    arquivo2.close();
    return 0;
}