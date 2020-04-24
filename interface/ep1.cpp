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
hashTable<Chave, Item>::hashTable(string nome_arquivo){}

template <class Chave, class Item>
hashTable<Chave, Item>::~hashTable(){}

template <class Chave, class Item>
void hashTable<Chave, Item>::printa(){}

template <class Chave, class Item>
void hashTable<Chave, Item>:: insere(Chave chave, Item valor){}

template <class Chave, class Item>
Item hashTable<Chave, Item>::devolve(Chave chave){}

template <class Chave, class Item>
void hashTable<Chave, Item>::remove(Chave chave){}

template <class Chave, class Item>
int hashTable<Chave, Item>::rank(Chave chave){}

template <class Chave, class Item>
Chave hashTable<Chave, Item>::seleciona(int k){}

/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/

template <class Chave, class Item>
arvoreRN<Chave, Item>::arvoreRN(string nome_arquivo){}

template <class Chave, class Item>
arvoreRN<Chave, Item>::~arvoreRN(){}

template <class Chave, class Item>
void arvoreRN<Chave, Item>::printa(){}

template <class Chave, class Item>
void arvoreRN<Chave, Item>:: insere(Chave chave, Item valor){}

template <class Chave, class Item>
Item arvoreRN<Chave, Item>::devolve(Chave chave){}

template <class Chave, class Item>
void arvoreRN<Chave, Item>::remove(Chave chave){}

template <class Chave, class Item>
int arvoreRN<Chave, Item>::rank(Chave chave){}

template <class Chave, class Item>
Chave arvoreRN<Chave, Item>::seleciona(int k){}

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