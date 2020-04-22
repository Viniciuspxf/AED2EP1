#include "tabeladesimbolos.hpp"
#include "util.hpp"
#include <string>
#include <fstream>
using namespace std;

template <class Chave, class Item>
listaDes<Chave, Item>::listaDes(string nome_arquivo): cabeca(new noLista<Chave, Item>[1]) {
    cabeca->proximo = nullptr;
    ifstream arquivo;
    Chave atual;
    Item valor;
    while (!arquivo.eof()) {
        arquivo >> atual;
        valor = devolve(atual);
        if (valor == -1) valor = 1;
        else valor++;
        insere(atual, valor);
    }
    arquivo.open(nome_arquivo);

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
void listaDes<Chave, Item>::insere(Chave chave, Item valor) {
    noLista<Chave, Item> *aux, *anterior;

    while (aux != nullptr) {
        if (chave.compare(aux->chave) == 0) {
            aux->valor = valor;
            return;
        }
        anterior = aux;
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
    noLista<Chave, Item> *anterior = cabeca, *atual = cabeca->proximo;
    
    while (atual != nullptr) {
        if (chave.compare(atual->chave) == 0) {
            return atual->valor;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return -1;
}

template <class Chave, class Item>
int listaDes<Chave, Item>::rank(Chave chave) {
    int contador = 0;
    noLista<Chave, Item> *aux;
    for (aux = cabeca->proximo; aux != nullptr; aux = aux->proximo) {
        if (aux->chave.compare(chave) < 0) contador++;
    }

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
    return nullptr;
}

/*------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/

template <class Chave, class Item>
listaOrd<Chave, Item>::listaOrd(string nome_arquivo): cabeca(new noLista<Chave, Item>[1]) {
    cabeca->proximo = nullptr;
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
void listaOrd<Chave, Item>::insere(Chave chave, Item valor) {
    noLista<Chave, Item> *atual = cabeca->proximo, *anterior = cabeca;
    int comparacao;
    while (atual != nullptr) {
        comparacao = chave.compare(atual->chave);
        if (comparacao == 0) {
            atual->chave = chave;
            return;
        }
        else if (comparacao < 0) break;
        
        anterior = atual;
        atual = atual->proximo;
    }

    anterior->proximo = new noLista<Chave, Item>[1];
    anterior->proximo->proximo = atual;
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
    noLista<Chave, Item> *atual = cabeca->proximo, *anterior = cabeca;
    int comparacao;
    while (atual != nullptr) {
        comparacao = chave.compare(atual->chave);
        if (comparacao == 0) {
            return atual->valor;
        }
        else if (comparacao < 0) break;
        anterior = atual;
        atual = atual->proximo;
    }
    return -1;
}

template <class Chave, class Item>
int listaOrd<Chave, Item>::rank(Chave chave) {
    int contador = 0, comparacao;
    noLista<Chave, Item> *atual;
    while (atual != nullptr) {
        comparacao = chave.compare(atual->chave);
        if (comparacao == 0) break;
        else if (comparacao > 0) contador++;
    }
    return contador;
}

template <class Chave, class Item>
Chave listaOrd<Chave, Item>::seleciona(int k) {
    noLista<Chave, Item> *atual;
    int i;
    for (atual = cabeca->proximo, i = 0; i < k; atual = atual->proximo, i++);
    
    return atual->chave;
}

/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/

template <class Chave, class Item>
arvoreBin<Chave, Item>::arvoreBin(string nome_arquivo): raiz(nullptr){};

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
        return nullptr;
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

                    no->esq->pai = no;
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
                    aux->esq->pai = aux->pai;
                }
                else {
                    aux->pai->esq = aux->esq;
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
vetorDes<Chave, Item>::vetorDes(string nome_arquivo){}

template <class Chave, class Item>
vetorDes<Chave, Item>::~vetorDes(){}

template <class Chave, class Item>
void vetorDes<Chave, Item>::insere(Chave chave, Item valor){}

template <class Chave, class Item>
Item vetorDes<Chave, Item>::devolve(Chave chave){}

template <class Chave, class Item>
void vetorDes<Chave, Item>::remove(Chave chave){}

template <class Chave, class Item>
int vetorDes<Chave, Item>::rank(Chave chave){}

template <class Chave, class Item>
Chave vetorDes<Chave, Item>::seleciona(int k){}

/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/

template <class Chave, class Item>
vetorOrd<Chave, Item>::vetorOrd(string nome_arquivo){}

template <class Chave, class Item>
vetorOrd<Chave, Item>::~vetorOrd(){}

template <class Chave, class Item>
void vetorOrd<Chave, Item>:: insere(Chave chave, Item valor){}

template <class Chave, class Item>
Item vetorOrd<Chave, Item>::devolve(Chave chave){}

template <class Chave, class Item>
void vetorOrd<Chave, Item>::remove(Chave chave){}

template <class Chave, class Item>
int vetorOrd<Chave, Item>::rank(Chave chave){}

template <class Chave, class Item>
Chave vetorOrd<Chave, Item>::seleciona(int k){}

/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/

template <class Chave, class Item>
treap<Chave, Item>::treap(string nome_arquivo){}

template <class Chave, class Item>
treap<Chave, Item>::~treap(){}

template <class Chave, class Item>
void treap<Chave, Item>:: insere(Chave chave, Item valor){}

template <class Chave, class Item>
Item treap<Chave, Item>::devolve(Chave chave){}

template <class Chave, class Item>
void treap<Chave, Item>::remove(Chave chave){}

template <class Chave, class Item>
int treap<Chave, Item>::rank(Chave chave){}

template <class Chave, class Item>
Chave treap<Chave, Item>::seleciona(int k){}

/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/

template <class Chave, class Item>
hashTable<Chave, Item>::hashTable(string nome_arquivo){}

template <class Chave, class Item>
hashTable<Chave, Item>::~hashTable(){}

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