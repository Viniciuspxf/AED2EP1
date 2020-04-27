#include "tabeladesimbolos.hpp"
#include "util.hpp"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool ehSimbolo(char caracter) {

    switch (caracter) {
        case '*':
            return true;
            break;
        case '?':
            return true;
            break;
        case '"':
            return true;
            break;
        case ';':
            return true;
            break;
        case ':':
            return true;
            break;
        case '{':
            return true;
            break;
        case '}':
            return true;
            break;
        case '[':
            return true;
            break;
        case ']':
            return true;
            break;
        case '-':
            return true;
            break;
        case '.':
            return true;
            break;
        case ',':
            return true;
            break;
        case '!':
            return true;
            break;
        case '(':
            return true;
            break;
        case ')':
            return true;
            break;
    }

    return false;
}

template <class Chave, class Item>
listaDes<Chave, Item>::listaDes(string nome_arquivo): cabeca(new noLista<Chave, Item>[1]) {
    cabeca->proximo = nullptr;
    ifstream arquivo;
    Chave atual;
    Item valor;
    long unsigned int i;

    arquivo.open(nome_arquivo);

    while (!arquivo.eof()) {
        arquivo >> atual;

        for (i = 0; i < atual.size() && ehSimbolo(atual[i]); i++);
        atual.erase(0, i);

        while (atual.size() != 0 && ehSimbolo(atual.back()))
            atual.pop_back();

        if (atual.size() != 0) {
            valor = devolve(atual);
            if (valor == -1) valor = 1;
            else valor++;
            insere(atual, valor);
        }
    }
    

    arquivo.close();
};

template <class Chave, class Item>
listaDes<Chave, Item>::~listaDes() {
    noLista<Chave, Item> *proximo;

    while (cabeca != nullptr) {
        proximo = cabeca->proximo;
        delete [] cabeca;
        cabeca = proximo;
    }
    
}

template <class Chave, class Item>
void listaDes<Chave, Item>::printa() {
    noLista<Chave, Item> *atual;

    for (atual = cabeca->proximo; atual != nullptr; atual = atual->proximo) {
        cout << atual->chave << ": "<< atual->valor << endl;
    } 
    
}


template <class Chave, class Item>
void listaDes<Chave, Item>::insere(Chave chave, Item valor) {
    noLista<Chave, Item> *aux;

    aux = cabeca->proximo;

    while (aux != nullptr) {
        if (chave.compare(aux->chave) == 0) {
            aux->valor = valor;
            return;
        }
        aux = aux->proximo;
    }
    noLista<Chave, Item> *novo = new noLista<Chave, Item>[1];
    novo->chave = chave;
    novo->valor = valor;
    aux = cabeca->proximo;
    novo->proximo = aux;
    cabeca->proximo = novo;
}

template <class Chave, class Item>
void listaDes<Chave, Item>::remove(Chave chave) {
    noLista<Chave, Item> *anterior = cabeca, *atual = cabeca->proximo;
    
    while (atual != nullptr) {
        if (chave.compare(atual->chave) == 0) {
            anterior->proximo = atual->proximo;
            delete [] atual;
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

template <class Chave, class Item>
Item listaDes<Chave, Item>::devolve(Chave chave) {
    noLista<Chave, Item> *atual = cabeca->proximo;
    
    while (atual != nullptr) {
        if (chave.compare(atual->chave) == 0) {
            return atual->valor;
        }
        atual = atual->proximo;
    }
    return -1;
}

template <class Chave, class Item>
int listaDes<Chave, Item>::rank(Chave chave) {
    int contador = 0;
    noLista<Chave, Item> *aux;
    bool achou = false;
    int comparacao;
    for (aux = cabeca->proximo; aux != nullptr; aux = aux->proximo) {
        comparacao = aux->chave.compare(chave);
        if (comparacao < 0) contador++;
        else if (comparacao == 0) achou = true;
    }
    if (!achou) contador = -1;

    return contador;
}

template <class Chave, class Item>
Chave listaDes<Chave, Item>::seleciona(int k) {
    noLista<Chave, Item> *aux;
    
    for (aux = cabeca->proximo; aux != nullptr; aux = aux->proximo) {
        if (rank(aux->chave) == k) {
            return aux->chave;
        }
    }
    return "";
}

/*------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/

template <class Chave, class Item>
listaOrd<Chave, Item>::listaOrd(string nome_arquivo): cabeca(new noLista<Chave, Item>[1]) {
    cabeca->proximo = nullptr;
    ifstream arquivo;
    Chave atual;
    Item valor;

    long unsigned int i;

    arquivo.open(nome_arquivo);

    while (!arquivo.eof()) {
        arquivo >> atual;

        for (i = 0; i < atual.size() && ehSimbolo(atual[i]); i++);
        atual.erase(0, i);

        while (atual.size() != 0 && ehSimbolo(atual.back()))
            atual.pop_back();

        if (atual.size() != 0) {
            valor = devolve(atual);
            if (valor == -1) valor = 1;
            else valor++;
            insere(atual, valor);
        }
    }
    

    arquivo.close();
};

template <class Chave, class Item>
listaOrd<Chave, Item>::~listaOrd() {
    noLista<Chave, Item> *aux;

    while (cabeca != nullptr) {
        aux = cabeca->proximo;
        delete [] cabeca;
        cabeca = aux;
    }

}

template <class Chave, class Item>
void listaOrd<Chave, Item>::printa() {
    noLista<Chave, Item> *atual;

    for (atual = cabeca->proximo; atual != nullptr; atual = atual->proximo) {
        cout << atual->chave << ": "<< atual->valor << endl;
    } 
    
}

template <class Chave, class Item>
void listaOrd<Chave, Item>::insere(Chave chave, Item valor) {
    noLista<Chave, Item> *atual = cabeca->proximo, *anterior = cabeca;
    int comparacao;
    while (atual != nullptr) {
        comparacao = chave.compare(atual->chave);
        if (comparacao == 0) {
            atual->valor = valor;
            return;
        }
        else if (comparacao < 0) break;
        
        anterior = atual;
        atual = atual->proximo;
    }
    noLista<Chave, Item> *novo = new noLista<Chave, Item>[1];
    novo->chave = chave;
    novo->valor = valor;
    anterior->proximo = novo;
    novo->proximo = atual;
}

template <class Chave, class Item>
void listaOrd<Chave, Item>::remove(Chave chave) {
    noLista<Chave, Item> *atual = cabeca->proximo, *anterior = cabeca;
    int comparacao;
    while (atual != nullptr) {
        comparacao = chave.compare(atual->chave);
        if (comparacao == 0) {
            anterior->proximo = atual->proximo;
            delete [] atual;
            break;
        }
        else if (comparacao < 0) break;
        anterior = atual;
        atual = atual->proximo;
    }
}

template <class Chave, class Item>
Item listaOrd<Chave, Item>::devolve(Chave chave) {
    noLista<Chave, Item> *atual = cabeca->proximo;
    int comparacao;
    while (atual != nullptr) {
        comparacao = chave.compare(atual->chave);
        if (comparacao == 0) {
            return atual->valor;
        }
        else if (comparacao < 0) break;
        atual = atual->proximo;
    }
    return -1;
}

template <class Chave, class Item>
int listaOrd<Chave, Item>::rank(Chave chave) {
    int contador = 0, comparacao;
    bool achou = false;
    noLista<Chave, Item> *atual = cabeca->proximo;
    while (atual != nullptr) {
        comparacao = chave.compare(atual->chave);
        if (comparacao == 0) {
            achou = true;
            break;
        }
        else if (comparacao > 0) contador++;
        else break;
        atual = atual->proximo;
    }
    if (!achou) contador = -1;
    return contador;
}

template <class Chave, class Item>
Chave listaOrd<Chave, Item>::seleciona(int k) {
    noLista<Chave, Item> *atual;
    int i;
    for (atual = cabeca->proximo, i = 0; i < k && atual != nullptr; atual = atual->proximo, i++);
    
    if (atual == nullptr) return "";

    return atual->chave;
}

/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/

template <class Chave, class Item>
arvoreBin<Chave, Item>::arvoreBin(string nome_arquivo): raiz(nullptr){
    ifstream arquivo;
    Chave atual;
    Item valor;
    long unsigned int i;

    arquivo.open(nome_arquivo);

    while (!arquivo.eof()) {
        arquivo >> atual;

        for (i = 0; i < atual.size() && ehSimbolo(atual[i]); i++);
        atual.erase(0, i);

        while (atual.size() != 0 && ehSimbolo(atual.back()))
            atual.pop_back();

        if (atual.size() != 0) {
            valor = devolve(atual);
            if (valor == -1) valor = 1;
            else valor++;
            insere(atual, valor);
        }
    }
    

    arquivo.close();
};

template <class Chave, class Item>
arvoreBin<Chave, Item>::~arvoreBin() {
    excluiArvore(raiz);
}

template <class Chave, class Item>
void arvoreBin<Chave, Item>::excluiArvore(noArvore<Chave, Item> *no) {
    if (no != nullptr) {
        excluiArvore(no->dir);
        excluiArvore(no->esq);
        delete [] no;
    }
}

template <class Chave, class Item>
void arvoreBin<Chave, Item>::printa(){
    printaR(raiz);
}

template <class Chave, class Item>
void arvoreBin<Chave, Item>::printaR(noArvore<Chave, Item> *no){
    if (no != nullptr) {
        printaR(no->esq);
        cout << no->chave << ": "<< no->valor << endl;
        printaR(no->dir);
    }
}

template <class Chave, class Item>
void arvoreBin<Chave, Item>::insere(Chave chave, Item valor) {
    raiz = insereR(raiz, chave, valor);
}

template <class Chave, class Item>
noArvore<Chave, Item> * arvoreBin<Chave, Item>::insereR(noArvore<Chave, Item> *no, Chave chave, Item valor) {
    int comparacao;

    if (no == nullptr) {
        no = new noArvore<Chave, Item>[1];
        no->dir = nullptr;
        no->esq = nullptr;
        no->chave = chave;
        no->valor = valor;
        no->pai = nullptr;
    }
    else {
        comparacao = no->chave.compare(chave);
        if (comparacao == 0)
            no->valor = valor;
        else if (comparacao > 0) {
            no->esq = insereR(no->esq, chave, valor);
            no->esq->pai = no;
        }
        else {
            no->dir = insereR(no->dir, chave, valor);
            no->dir->pai = no;
        }
    }

    return no;
}

template <class Chave, class Item>
Item arvoreBin<Chave, Item>::devolve(Chave chave) {
    return devolveR(raiz, chave);
}

template <class Chave, class Item>
Item arvoreBin<Chave, Item>::devolveR(noArvore<Chave, Item> *no, Chave chave) {
    int comparacao;
    if (no != nullptr) {
        comparacao = no->chave.compare(chave);
        if (comparacao == 0) 
            return no->valor;
        else if (comparacao > 0) 
            return devolveR(no->esq, chave);
        else 
            return devolveR(no->dir, chave);
    }
    return -1;
}

template <class Chave, class Item>
int arvoreBin<Chave, Item>::rank(Chave chave) {
    noArvore<Chave, Item> *no;
    no = raiz;
    int comparacao, contador = 0;
    while (no != nullptr) {
        comparacao = no->chave.compare(chave);
        if (comparacao == 0)
            break;
        else if (comparacao > 0)
            no = no->esq;
        else no = no->dir;
    }
    if (no == nullptr) return -1;

    contador = contaNos(no->esq) + 1;

    while (no->pai != nullptr && no->pai->dir == no) {
        no = no->pai;
        contador++;
        contador += contaNos(no->esq) + 1;
    }
    return contador;
}

template<class Chave, class Item>
int arvoreBin<Chave, Item>::contaNos(noArvore<Chave, Item> *no) {
    int contador = 0;
    if (no == nullptr) {
        return -1;
    }
    else {
        contador = contaNos(no->esq) + 1;
        contador += contaNos(no->dir) + 1;
    }
    return contador;
}

template <class Chave, class Item>
Chave arvoreBin<Chave, Item>::seleciona(int k) {
    int contador = -1;
    return selecionaR(raiz, k, &contador);
}

template <class Chave, class Item>
Chave arvoreBin<Chave, Item>::selecionaR(noArvore<Chave, Item> *no, int k, int *contador) {
    Chave chave;
    if (no == nullptr) {
        return "";
    }
    else {
        chave = selecionaR(no->esq, k, contador);
        if (*contador == k) return chave;
        *contador += 1;
        if (k == *contador) return no->chave;
        return selecionaR(no->dir, k, contador);
    }
}

template <class Chave, class Item>
void arvoreBin<Chave, Item>::remove(Chave chave) {
    raiz = removeR(raiz, chave);
}

template <class Chave, class Item>
noArvore<Chave, Item> * arvoreBin<Chave, Item>::removeR(noArvore<Chave, Item> *no, Chave chave) {
    int comparacao;
    noArvore<Chave, Item> *aux;
    if (no != nullptr) {
        comparacao = no->chave.compare(chave);
        if (comparacao == 0) {
            if (no->esq == nullptr) {
                if (no->dir != nullptr) {
                    aux = no->dir;
                    
                    no->chave = aux->chave;
                    no->valor = aux->valor;

                    no->esq = aux->esq;
                    no->dir = aux->dir;

                    if (no->esq != nullptr)
                        no->esq->pai = no;

                    if (no->dir != nullptr)
                        no->dir->pai = no;
                }
                else {
                    aux = no;
                    no = nullptr;
                }
            }
            else {
                aux = no->esq;
                while (aux->dir != nullptr) aux = aux->dir; 

                no->chave = aux->chave;
                no->valor = aux->valor;

                if (aux == aux->pai->dir) {
                    aux->pai->dir = aux->esq;
                    if (aux->esq != nullptr)
                        aux->esq->pai = aux->pai;
                }
                else {
                    aux->pai->esq = aux->esq;
                    if (aux->esq != nullptr)
                        aux->esq->pai = aux->pai;
                }
            }

            delete [] aux;
        }
        else if (comparacao > 0) {
            no->esq = removeR(no->esq, chave);
        }
        else {
            no->dir = removeR(no->dir, chave);
        }
    }
    return no;
}
/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/

template <class Chave, class Item>
vetorDes<Chave, Item>::vetorDes(string nome_arquivo) {
    n = 0;
    max = 2000;
    vetor = new celula<Chave, Item>[max];

    ifstream arquivo;
    Chave atual;
    Item valor;
    long unsigned int i;

    arquivo.open(nome_arquivo);

    while (!arquivo.eof()) {
        arquivo >> atual;

        for (i = 0; i < atual.size() && ehSimbolo(atual[i]); i++);
        atual.erase(0, i);

        while (atual.size() != 0 && ehSimbolo(atual.back()))
            atual.pop_back();

        if (atual.size() != 0) {
            valor = devolve(atual);
            if (valor == -1) valor = 1;
            else valor++;
            insere(atual, valor);
        }
    }

    arquivo.close();
}

template <class Chave, class Item>
vetorDes<Chave, Item>::~vetorDes() {
    delete [] vetor;
}

template <class Chave, class Item>
void vetorDes<Chave, Item>::printa() {
    int i;
    
    for (i = 0; i < n; i++)
        cout << vetor[i].chave << ": " << vetor[i].valor << endl;
}

template <class Chave, class Item>
void vetorDes<Chave, Item>::insere(Chave chave, Item valor) {
    int i;

    for (i = 0; i < n; i++) {
        if (chave.compare(vetor[i].chave) == 0) {
            vetor[i].valor =  valor;
            return;
        }
    }

    if (n + 1 > max)
        resize();

    vetor[n].chave = chave;
    vetor[n].valor = valor;
    n++; 
}

template <class Chave, class Item>
void vetorDes<Chave, Item>::resize() {
    int i;
    celula<Chave, Item> *novo = new celula<Chave, Item>[2*max], *aux;
    max = 2*max;
    for (i = 0; i < n; i++)
        novo[i] = vetor[i];

    aux = vetor;
    vetor = novo;
    delete [] aux;

}


template <class Chave, class Item>
Item vetorDes<Chave, Item>::devolve(Chave chave) {
    int i;

    for (i = 0; i < n; i++) {
        if (chave.compare(vetor[i].chave) == 0) 
            return vetor[i].valor;
    }

    return -1;
}

template <class Chave, class Item>
void vetorDes<Chave, Item>::remove(Chave chave) {
    int i;

    for (i = 0; i < n; i++) {
        if (chave.compare(vetor[i].chave) == 0) {
            for (; i < n - 1; i++) {
                vetor[i].chave = vetor[i + 1].chave;
                vetor[i].valor = vetor[i + 1].valor;
            }
            n--;
            return;
        }
    }
}

template <class Chave, class Item>
int vetorDes<Chave, Item>::rank(Chave chave) {
    int i, contador = 0, comparacao;
    bool achou = false;

    for (i = 0; i < n; i++) {
        comparacao = chave.compare(vetor[i].chave);
        if (comparacao == 0) 
            achou = true;
        else if (comparacao > 0)
            contador++;
    }

    if (!achou) contador = -1;

    return contador;
}

template <class Chave, class Item>
Chave vetorDes<Chave, Item>::seleciona(int k) {
    int i;
    
    for (i = 0; i < n; i++) {
        if (rank(vetor[i].chave) == k)
            return vetor[i].chave;
    }

    return "";
}

/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/

template <class Chave, class Item>
vetorOrd<Chave, Item>::vetorOrd(string nome_arquivo){
    n = 0;
    max = 2000;
    vetor = new celula<Chave, Item>[max];

    ifstream arquivo;
    Chave atual;
    Item valor;
    long unsigned int i;

    arquivo.open(nome_arquivo);

    while (!arquivo.eof()) {
        arquivo >> atual;

        for (i = 0; i < atual.size() && ehSimbolo(atual[i]); i++);
        atual.erase(0, i);

        while (atual.size() != 0 && ehSimbolo(atual.back()))
            atual.pop_back();

        if (atual.size() != 0) {
            valor = devolve(atual);
            if (valor == -1) valor = 1;
            else valor++;
            insere(atual, valor);
        }
    }

    arquivo.close();
}

template <class Chave, class Item>
vetorOrd<Chave, Item>::~vetorOrd(){
    delete [] vetor;
}

template <class Chave, class Item>
void vetorOrd<Chave, Item>::printa(){
    int i;
    for (i = 0; i < n; i++)
        cout << vetor[i].chave << ": " << vetor[i].valor << endl;
}

template <class Chave, class Item>
void vetorOrd<Chave, Item>:: insere(Chave chave, Item valor) {
    if (n + 1 > max) resize();
    int i, k, a, b, comparacao;

    a = 0;
    b = n - 1;

    while (a <= b) {
        i = (a+b)/2;
        comparacao = chave.compare(vetor[i].chave);
        if (comparacao < 0)
            b = i - 1;
        else if (comparacao > 0)
            a = i + 1;
        else {
            vetor[i].valor = valor;
            return;
        }
    }

    i = a;

    for (k = n; k > i; k--) {
        vetor[k].chave = vetor[k - 1].chave;
        vetor[k].valor = vetor[k - 1].valor;
    }
    vetor[i].valor = valor;
    vetor[i].chave = chave;
    
    n++;
}

template <class Chave, class Item>
void vetorOrd<Chave, Item>::resize() {
    int i;
    celula<Chave, Item> *novo = new celula<Chave, Item>[2*max], *aux;
    max = 2*max;
    for (i = 0; i < n; i++)
        novo[i] = vetor[i];

    aux = vetor;
    vetor = novo;
    delete [] aux;
}

template <class Chave, class Item>
Item vetorOrd<Chave, Item>::devolve(Chave chave){
    int a, b, comparacao, i;
    a = 0;
    b = n - 1;

    while (a <= b) {
        i = (a+b)/2;
        comparacao = chave.compare(vetor[i].chave);
        if (comparacao < 0)
            b = i - 1;
        else if (comparacao > 0)
            a = i + 1;
        else {
            return vetor[i].valor;
        }
    }
    return -1;
}

template <class Chave, class Item>
void vetorOrd<Chave, Item>::remove(Chave chave){
    int a, b, comparacao, i, j;
    a = 0;
    b = n - 1;

    while (a <= b) {
        i = (a+b)/2;
        comparacao = chave.compare(vetor[i].chave);
        if (comparacao < 0)
            b = i - 1;
        else if (comparacao > 0)
            a = i + 1;
        else {
            for (j = i; j < n - 1; j++) {
                vetor[j].chave = vetor[j + 1].chave;
                vetor[j].valor = vetor[j + 1].valor;
                n--;
                break;
            }

        }
    }
}

template <class Chave, class Item>
int vetorOrd<Chave, Item>::rank(Chave chave){
    int i;

    for (i = 0; i < n && chave.compare(vetor[i].chave) > 0; i++)

    if (i < n && chave.compare(vetor[i].chave) == 0) return i;
    
    return -1;
}

template <class Chave, class Item>
Chave vetorOrd<Chave, Item>::seleciona(int k){
    if (k >= 0 && k < n) return vetor[k].chave;
    
    return "";
}

/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/

template <class Chave, class Item>
treap<Chave, Item>::treap(string nome_arquivo): raiz(nullptr) {
    ifstream arquivo;
    Chave atual;
    Item valor;
    long unsigned int i;

    arquivo.open(nome_arquivo);

    while (!arquivo.eof()) {
        arquivo >> atual;

        for (i = 0; i < atual.size() && ehSimbolo(atual[i]); i++);
        atual.erase(0, i);

        while (atual.size() != 0 && ehSimbolo(atual.back()))
            atual.pop_back();

        if (atual.size() != 0) {
            valor = devolve(atual);
            if (valor == -1) valor = 1;
            else valor++;
            insere(atual, valor);
        }
    }
    

    arquivo.close();
};

template <class Chave, class Item>
treap<Chave, Item>::~treap(){
    excluiArvore(raiz);
}

template <class Chave, class Item>
void treap<Chave, Item>::excluiArvore(noTreap<Chave, Item> *no) {
    if (no != nullptr) {
        excluiArvore(no->dir);
        excluiArvore(no->esq);
        delete [] no;
    }
}



template <class Chave, class Item>
void treap<Chave, Item>::printa(){
    printaR(raiz);
}

template <class Chave, class Item>
void treap<Chave, Item>::printaR(noTreap<Chave, Item> *no){
    if (no != nullptr) {
        printaR(no->esq);
        cout << no->chave << ": "<< no->valor << endl;
        printaR(no->dir);
    }
}

template <class Chave, class Item>
void treap<Chave, Item>::insere(Chave chave, Item valor) {
    raiz = insereR(raiz, chave, valor);
}

template <class Chave, class Item>
noTreap<Chave, Item> * treap<Chave, Item>::insereR(noTreap<Chave, Item> *no, Chave chave, Item valor) {
    int comparacao;

    if (no == nullptr) {
        no = new noTreap<Chave, Item>[1];
        no->dir = nullptr;
        no->esq = nullptr;
        no->chave = chave;
        no->valor = valor;
        no->pai = nullptr;
        no->prioridade = rand();
    }
    else {
        comparacao = no->chave.compare(chave);
        if (comparacao == 0)
            no->valor = valor;
        else if (comparacao > 0) {
            no->esq = insereR(no->esq, chave, valor);
            no->esq->pai = no;

            if (no->esq->prioridade > no->prioridade) {
                noTreap<Chave, Item> *aux;
                aux = no;
                no = no->esq;

                no->pai = nullptr;
                aux->esq = no->dir;

                if (aux->esq != nullptr) 
                    aux->esq->pai = aux;

                no->dir = aux;
                aux->pai = no;
            }
        }
        else {
            no->dir = insereR(no->dir, chave, valor);
            no->dir->pai = no;

            if (no->dir->prioridade > no->prioridade) {
                noTreap<Chave, Item> *aux;
                aux = no;
                no = no->dir;

                no->pai = nullptr;
                aux->dir = no->esq;

                if (aux->dir != nullptr) 
                    aux->dir->pai = aux;

                no->esq = aux;
                aux->pai = no;
            }
        }
    }

    return no;
}


template <class Chave, class Item>
Item treap<Chave, Item>::devolve(Chave chave){
    return devolveR(raiz, chave);
}

template <class Chave, class Item>
Item treap<Chave, Item>::devolveR(noTreap<Chave, Item> *no, Chave chave) {
    int comparacao;
    if (no != nullptr) {
        comparacao = no->chave.compare(chave);
        if (comparacao == 0) 
            return no->valor;
        else if (comparacao > 0) 
            return devolveR(no->esq, chave);
        else 
            return devolveR(no->dir, chave);
    }
    return -1;
}


template <class Chave, class Item>
void treap<Chave, Item>::remove(Chave chave){
    raiz = removeR(raiz, chave);
}

template <class Chave, class Item>
noTreap<Chave, Item> * treap<Chave, Item>::removeR(noTreap<Chave, Item> *no, Chave chave) {
    int comparacao;
    noTreap<Chave, Item> *aux;
    if (no != nullptr) {
        comparacao = no->chave.compare(chave);
        if (comparacao == 0) {
            if (no->esq == nullptr) {
                if (no->dir != nullptr) {
                    aux = no->dir;
                    
                    no->chave = aux->chave;
                    no->valor = aux->valor;

                    no->esq = aux->esq;
                    no->dir = aux->dir;

                    if (no->esq != nullptr)
                        no->esq->pai = no;

                    if (no->dir != nullptr)
                        no->dir->pai = no;
                }
                else {
                    aux = no;
                    no = nullptr;
                }
            }
            else {
                aux = no->esq;
                while (aux->dir != nullptr) aux = aux->dir; 

                no->chave = aux->chave;
                no->valor = aux->valor;

                if (aux == aux->pai->dir) {
                    aux->pai->dir = aux->esq;
                    if (aux->esq != nullptr)
                        aux->esq->pai = aux->pai;
                }
                else {
                    aux->pai->esq = aux->esq;
                    if (aux->esq != nullptr)
                        aux->esq->pai = aux->pai;
                }
            }

            delete [] aux;
        }
        else if (comparacao > 0) {
            no->esq = removeR(no->esq, chave);
        }
        else {
            no->dir = removeR(no->dir, chave);
        }
    }
    return no;
}

template <class Chave, class Item>
int treap<Chave, Item>::rank(Chave chave) {
    noTreap<Chave, Item> *no;
    no = raiz;
    int comparacao, contador = 0;
    while (no != nullptr) {
        comparacao = no->chave.compare(chave);
        if (comparacao == 0)
            break;
        else if (comparacao > 0)
            no = no->esq;
        else no = no->dir;
    }
    if (no == nullptr) return -1;

    contador = contaNos(no->esq) + 1;

    while (no->pai != nullptr && no->pai->dir == no) {
        no = no->pai;
        contador++;
        contador += contaNos(no->esq) + 1;
    }
    return contador;
}

template<class Chave, class Item>
int treap<Chave, Item>::contaNos(noTreap<Chave, Item> *no) {
    int contador = 0;
    if (no == nullptr) {
        return -1;
    }
    else {
        contador = contaNos(no->esq) + 1;
        contador += contaNos(no->dir) + 1;
    }
    return contador;
}

template <class Chave, class Item>
Chave treap<Chave, Item>::seleciona(int k){
    int contador = -1;
    return selecionaR(raiz, k, &contador);
}

template <class Chave, class Item>
Chave treap<Chave, Item>::selecionaR(noTreap<Chave, Item> *no, int k, int *contador) {
    Chave chave;
    if (no == nullptr) {
        return "";
    }
    else {
        chave = selecionaR(no->esq, k, contador);
        if (*contador == k) return chave;
        *contador += 1;
        if (k == *contador) return no->chave;
        return selecionaR(no->dir, k, contador);
    }
}


/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/

template <class Chave, class Item>
int hashTable<Chave, Item>::hash(Chave chave) {
    int i, potencia = 1, valor = 0;

    for (i = 0; i < (int) chave.size(); i++) {
        valor += chave[i]*potencia;
        potencia = potencia*128;
    }

    return valor%m;
}

template <class Chave, class Item>
hashTable<Chave, Item>::hashTable(string nome_arquivo) {
    m = 3989;
    int i;
    table = new noLista<Chave, Item>*[m];
    for (i = 0; i < m; i++) {
        table[i] = new noLista<Chave, Item>[1];
        table[i]->proximo = nullptr;
    }
}

template <class Chave, class Item>
hashTable<Chave, Item>::~hashTable() {
    noLista<Chave,Item> *aux;
    int i;
    for (i = 0; i < m; i++) {
        for (aux = table[i]; aux != nullptr; aux = aux->proximo)
            delete [] aux;
    }

    delete [] table;
}

template <class Chave, class Item>
void hashTable<Chave, Item>::printa() {
    int i;
    noLista<Chave,Item> *aux;
    for (i = 0; i < m; i++) {
        for (aux = table[i]->proximo; aux != nullptr; aux = aux->proximo)
            cout << table[i]->chave << ": " << table[i]->valor << endl;
    }
}

template <class Chave, class Item>
void hashTable<Chave, Item>:: insere(Chave chave, Item valor){
    int indice = hash(chave);
    noLista<Chave,Item> *aux;

    for (aux = table[indice]->proximo; aux != nullptr; aux = aux->proximo) {
        if (aux->chave == chave) {
            aux->valor = valor;
            return;
        }
    }

    aux = table[indice]->proximo;
    noLista<Chave,Item> *novo = new noLista<Chave, Item>[1];
    novo->chave = chave;
    novo->valor = valor;
    novo->proximo = aux;
    table[indice]->proximo = novo;
}

template <class Chave, class Item>
Item hashTable<Chave, Item>::devolve(Chave chave){
    int indice = hash(chave);
    noLista<Chave,Item> *aux;

    for (aux = table[indice]->proximo; aux != nullptr; aux = aux->proximo) {
        if (aux->chave == chave) {   
            return aux->valor;
        }
    }
    return -1;
}

template <class Chave, class Item>
void hashTable<Chave, Item>::remove(Chave chave) {
    int indice = hash(chave);
    noLista<Chave,Item> *aux, *anterior;

    anterior = table[indice];
    for (aux = table[indice]->proximo; aux != nullptr; aux = aux->proximo) {
        if (aux->chave == chave) {   
            anterior->proximo = aux->proximo;
            delete [] aux;
            return;
        }
        anterior = aux;
    }
}

template <class Chave, class Item>
int hashTable<Chave, Item>::rank(Chave chave) {
    int indice = hash(chave), i;
    noLista<Chave,Item> *aux;
    bool achou = false;

    for (aux = table[indice]->proximo; aux != nullptr; aux = aux->proximo) {
        if (aux->chave == chave) {   
            achou = true;
        }
    }

    if (achou) {
        int contador = 0;
        for (i = 0;  i < m; i++ ) {
            for (aux = table[i]->proximo; aux != nullptr; aux = aux->proximo) {
                if (aux->chave < chave) contador++;
            }
        }

        return contador;
    }
    return -1;
}

template <class Chave, class Item>
Chave hashTable<Chave, Item>::seleciona(int k) {
    int i;
    noLista<Chave,Item> *aux;
    for (i = 0;  i < m; i++ ) {
        for (aux = table[i]->proximo; aux != nullptr; aux = aux->proximo) {
            if (rank(aux->chave) == k) return aux->chave;
        }
    }
    return "";
}

/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/

template <class Chave, class Item>
arvoreRN<Chave, Item>::arvoreRN(string nome_arquivo): raiz(nullptr){
    ifstream arquivo;
    Chave atual;
    Item valor;
    long unsigned int i, j = 0;

    arquivo.open(nome_arquivo);

    while (!arquivo.eof()) {
        arquivo >> atual;

        for (i = 0; i < atual.size() && ehSimbolo(atual[i]); i++);
        atual.erase(0, i);

        while (atual.size() != 0 && ehSimbolo(atual.back()))
            atual.pop_back();

        if (atual.size() != 0) {
            valor = devolve(atual);
            if (valor == -1) valor = 1;
            else valor++;
            insere(atual, valor);
        }
        cout << endl;
        cout << j << ":" << endl;
        printa();
        j++;
    }
    

    arquivo.close();
};

template <class Chave, class Item>
arvoreRN<Chave, Item>::~arvoreRN() {
    excluiArvore(raiz);
}

template <class Chave, class Item>
void arvoreRN<Chave, Item>::excluiArvore(noRN<Chave, Item> *no) {
    if (no != nullptr) {
        excluiArvore(no->dir);
        excluiArvore(no->esq);
        delete [] no;
    }
}

template <class Chave, class Item>
void arvoreRN<Chave, Item>::printa() {
    printaR(raiz);
}

template <class Chave, class Item>
void arvoreRN<Chave, Item>::printaR(noRN<Chave, Item> *no){
    if (no != nullptr) {
        printaR(no->esq);
        cout << no->chave << ": "<< no->valor << endl;
        printaR(no->dir);
    }
}

template <class Chave, class Item>
void arvoreRN<Chave, Item>:: insere(Chave chave, Item valor) {
    int comparacao;
    bool desbalanceado;
    if (raiz == nullptr) {
        raiz = new noRN<Chave, Item>[1];
        raiz->pai = nullptr;
        raiz->esq = nullptr;
        raiz->dir = nullptr;
        raiz->chave = chave;
        raiz->valor = valor;
        raiz->black = 1;
        return;
    }


    noRN<Chave, Item> *atual = raiz, *anterior;

    while (atual != nullptr) {
        comparacao = chave.compare(atual->chave);
        if (comparacao == 0) {
            atual->valor = valor;
            return;
        }
        else {
            anterior = atual;
            if (comparacao < 0) {
                atual = atual->esq;
            }
            else {
                atual = atual->dir;
            }
        }
    }

    atual = new noRN<Chave, Item>[1];
    atual->chave = chave;
    atual->valor = valor;
    atual->pai = anterior;
    atual->esq = nullptr;
    atual->dir = nullptr;
    atual->black = 0;

    if (comparacao < 0) 
        anterior->esq = atual;
    else
        anterior->dir = atual;
    
    desbalanceado = true;

    while (desbalanceado) {
        noRN<Chave, Item> *pai, *avo, *tio;
        pai = atual->pai;
    
        if (pai == nullptr) {
            atual->black = 1;
            desbalanceado = false;
        }
        else if (pai->black == 1)
            desbalanceado = false;
        else {
            avo = atual->pai->pai;
            tio = (avo->esq == pai ? avo->dir : avo->esq); 
            
            if (tio != nullptr && tio->black == 0) {
                avo->black = 0;
                pai->black = tio->black = 1;
                atual = avo;
            }
            else if (avo->esq == tio && pai->esq == atual) {
                rotacionaDir(pai);
                atual = pai;
            }
            else if (avo->dir == tio && pai->dir == atual) {
                rotacionaEsq(pai);
                atual = pai;
            }
            else if (avo->esq == tio && pai->dir == atual) {
                rotacionaEsq(avo);

                pai->black = 1;
                avo->black = 0;
            }
            else if (avo->dir == tio && pai->esq == atual) {
                rotacionaDir(avo);

                pai->black = 1;
                avo->black = 0;

            }       
        }
    }


}

template <class Chave, class Item>
Item arvoreRN<Chave, Item>::devolve(Chave chave) {
    return devolveR(raiz, chave);
}

template <class Chave, class Item>
Item arvoreRN<Chave, Item>::devolveR(noRN<Chave, Item> *no, Chave chave) {
    int comparacao;
    if (no != nullptr) {
        comparacao = no->chave.compare(chave);
        if (comparacao == 0) 
            return no->valor;
        else if (comparacao > 0) 
            return devolveR(no->esq, chave);
        else 
            return devolveR(no->dir, chave);
    }
    return -1;
}

template <class Chave, class Item>
void arvoreRN<Chave, Item>::remove(Chave chave) {
    noRN<Chave, Item> *atual = raiz, *aux, *aux2, *pai, *irmao, *excluido;
    int comparacao;

    while (atual != nullptr) {
        comparacao = chave.compare(atual->chave);
        if (comparacao == 0) 
            break;
        else if (comparacao < 0)
            atual = atual->esq;
        else 
            atual = atual->dir;
    }

    if (atual != nullptr) {
        if (atual->esq != nullptr) {
            aux = atual->esq;

            while (aux->dir != nullptr) aux = aux->dir;
            
            atual->chave = aux->chave;
            atual->valor = atual->valor;
        }
    }
    else return;

    if (aux->black == 0) {
        if (aux->dir != nullptr || aux->esq != nullptr ) {
            if (aux->dir != nullptr)
                aux2 = aux->dir;
            else
                aux2 = aux->esq;

            aux->chave = aux2->chave;
            aux->valor = aux2->valor;
            aux->black = aux2->black;

            aux->esq = aux2->esq;
            aux->dir = aux2->dir;

            if (aux->esq != nullptr)
                aux->esq->pai = aux;

            if (aux->dir != nullptr)
                aux->dir->pai = aux;
        }
        else {
            if (aux->pai->esq == aux) {
                aux->pai->esq = nullptr;
            }

            if (aux->pai->dir == aux) {
                aux->pai->dir = nullptr;
            }
            aux2 = aux;
        }

        delete [] aux2;
        return;
    }
    else {
        if (aux->esq != nullptr && aux->esq->black == 0) {
            aux2 = aux->esq;
            aux->chave = aux2->chave;
            aux->valor = aux2->valor;
            aux->esq = nullptr;
            delete [] aux2;
            return;
        }
        else if (aux->dir != nullptr && aux->dir->black == 0) {
            aux2 = aux->dir;
            aux->chave = aux2->chave;
            aux->valor = aux2->valor;
            aux->dir = nullptr;
            delete [] aux2;
            return;
        }
    }
    
    aux->chave = "";
    aux->black = 2;
    excluido = aux;

    while (aux->black == 2) {
        if (aux == raiz) {
            raiz->black = 1;
        }
        else {
            pai = aux->pai;
            irmao = (pai->esq == aux ? pai->dir : pai->esq);

            if (irmao != nullptr && irmao->black == 0) {
                pai->black = 0;
                irmao->black = 1;
                
                if (pai->esq == aux) 
                    rotacionaEsq(pai);
                
                else 
                    rotacionaDir(pai);
                
            }
            else if (pai->esq == aux && irmao->dir != nullptr && irmao->dir->black == 0) {
                int cor;

                cor = pai->black;
                pai->black = irmao->black;
                irmao->black = cor;
                rotacionaEsq(pai);
                aux->black--;
                irmao->dir->black = 1;
            }

            else if (pai->dir == aux && irmao->esq != nullptr && irmao->esq->black == 0) {
                int cor;

                cor = pai->black;
                pai->black = irmao->black;
                irmao->black = cor;
                rotacionaDir(pai);
                aux->black--;
                irmao->esq->black = 1;
            }

            else if (pai->esq == aux && irmao->esq != nullptr && irmao->esq->black == 0) {
                irmao->black = 0;
                irmao->esq->black = 1;
                rotacionaDir(irmao);
            }

            else if (pai->dir == aux && irmao->dir != nullptr && irmao->dir->black == 0) {
                irmao->black = 0;
                irmao->dir->black = 1;
                rotacionaEsq(irmao);
            }
            else {
                aux->black--;
                pai->black++;
                irmao->black = 0;
                aux = pai;
            }
        }
    }

    if (excluido->pai != nullptr) {
        pai = excluido->pai;
        if (pai->dir == excluido) {

            if (excluido->dir != nullptr) {
                pai->dir = excluido->dir;
                pai->dir->pai = pai;
                
            }
            else if (excluido->esq != nullptr) {
                pai->dir = excluido->esq;
                pai->dir->pai = pai;
            
            }
            else {
                pai->dir = nullptr;
            }

        }
        else if (pai->esq == excluido) {
            if (excluido->dir != nullptr) {
                pai->esq = excluido->dir;
                pai->esq->pai = pai;
                
            }
            else if (excluido->esq != nullptr) {
                pai->esq = excluido->esq;
                pai->esq->pai = pai;
            
            }
            else {
                pai->esq = nullptr;
            }
        }

    }
    else {
        raiz = nullptr;
    }
    delete [] excluido;
}


template <class Chave, class Item>
void arvoreRN<Chave, Item>::rotacionaEsq(noRN<Chave, Item> *no) {
    noRN<Chave, Item> *aux, *pai;

    pai = no->pai;
    aux = no->dir;

    no->dir  = aux->esq;

    if (no->dir != nullptr) 
        no->dir->pai = nullptr;
    
    aux->esq  = no;
    no->pai = aux;

    if (pai != nullptr) {
        if (pai->esq == no)
            pai->esq = aux;
        else 
            pai->dir = aux;

        aux->pai = pai;
    }
    else raiz = aux;
}

template <class Chave, class Item>
void arvoreRN<Chave, Item>::rotacionaDir(noRN<Chave, Item> *no) {
noRN<Chave, Item> *aux, *pai;

    pai = no->pai;
    aux = no->esq;

    no->esq  = aux->dir;

    if (no->esq != nullptr) 
        no->esq->pai = nullptr;
    
    aux->dir  = no;
    no->pai = aux;

    aux->pai = pai;

    if (pai != nullptr) {
        if (pai->esq == no)
            pai->esq = aux;
        else 
            pai->dir = aux;  
    }
    else raiz = aux;
}

template <class Chave, class Item>
int arvoreRN<Chave, Item>::rank(Chave chave) {
    noRN<Chave, Item> *no;
    no = raiz;
    int comparacao, contador = 0;
    while (no != nullptr) {
        comparacao = no->chave.compare(chave);
        if (comparacao == 0)
            break;
        else if (comparacao > 0)
            no = no->esq;
        else no = no->dir;
    }
    if (no == nullptr) return -1;

    contador = contaNos(no->esq) + 1;

    while (no->pai != nullptr && no->pai->dir == no) {
        no = no->pai;
        contador++;
        contador += contaNos(no->esq) + 1;
    }
    return contador;
}

template<class Chave, class Item>
int arvoreRN<Chave, Item>::contaNos(noRN<Chave, Item> *no) {
    int contador = 0;
    if (no == nullptr) {
        return -1;
    }
    else {
        contador = contaNos(no->esq) + 1;
        contador += contaNos(no->dir) + 1;
    }
    return contador;
}

template <class Chave, class Item>
Chave arvoreRN<Chave, Item>::seleciona(int k) {
    int contador = -1;
    return selecionaR(raiz, k, &contador);
}

template <class Chave, class Item>
Chave arvoreRN<Chave, Item>::selecionaR(noRN<Chave, Item> *no, int k, int *contador) {
    Chave chave;
    if (no == nullptr) {
        return "";
    }
    else {
        chave = selecionaR(no->esq, k, contador);
        if (*contador == k) return chave;
        *contador += 1;
        if (k == *contador) return no->chave;
        return selecionaR(no->dir, k, contador);
    }
}

/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/

template <class Chave, class Item>
arvore23<Chave, Item>::arvore23(string nome_arquivo){}

template <class Chave, class Item>
arvore23<Chave, Item>::~arvore23(){}

template <class Chave, class Item>
void arvore23<Chave, Item>::printa(){}

template <class Chave, class Item>
void arvore23<Chave, Item>:: insere(Chave chave, Item valor){}

template <class Chave, class Item>
Item arvore23<Chave, Item>::devolve(Chave chave){}

template <class Chave, class Item>
void arvore23<Chave, Item>::remove(Chave chave){}

template <class Chave, class Item>
int arvore23<Chave, Item>::rank(Chave chave){}

template <class Chave, class Item>
Chave arvore23<Chave, Item>::seleciona(int k){}

/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/*  insere garantir que está funcionando
    remove nada acontece
    devolve inválido retorna -1
    rank inválido retorna -1
    seleciona inválido retorna ""
    

*/
/*Depois, implementar diferentes lados para árvore binária (se sobrar tempo)*/

template class vetorOrd<string, int>;
template class vetorDes<string, int>;
template class listaOrd<string, int>;
template class listaDes<string, int>;
template class arvoreBin<string, int>;
template class arvore23<string, int>;
template class arvoreRN<string, int>;
template class hashTable<string, int>;
template class treap<string, int>;