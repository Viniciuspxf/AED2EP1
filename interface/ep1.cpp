#include "tabeladesimbolos.hpp"
#include "util.hpp"
#include <string>
using namespace std;

template <class Chave, class Item>
listaDes<Chave, Item>::listaDes(string nome_arquivo): cabeca(new noLista[1]) {
    cabeca->proximo = nullptr;
};

template <class Chave, class Item>
listaDes<Chave, Item>::~listaDes() {
    noLista *proximo;

    while (cabeca != nullptr) {
        proximo = cabeca->proximo;
        delete [] cabeca;
        cabeca = proximo;
    }
    
}

template <class Chave, class Item>
void listaDes<Chave, Item>::insere(Chave chave, Item valor) {
    noLista *aux, *anterior;

    while (aux != nullptr) {
        if (strCmp(chave, aux->chave) == 0) {
            aux->valor = valor;
            return;
        }
        anterior = aux;
        aux = aux->proximo;
    }
    noLista *novo = new noLista[1];
    novo->chave = chave;
    novo->valor = valor;
    aux = cabeca->prox;
    novo->proximo = aux;
    cabeca->proximo = novo;
}

template <class Chave, class Item>
void listaDes<Chave, Item>::remove(Chave chave) {
    noLista *anterior = cabeca, *atual = cabeca->proximo;
    
    while (atual != nullptr) {
        if (strCmp(chave, atual->chave) == 0) {
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
    noLista *anterior = cabeca, *atual = cabeca->proximo;
    
    while (atual != nullptr) {
        if (strCmp(chave, atual->chave) == 0) {
            return atual->valor;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return nullptr;
}

template <class Chave, class Item>
int listaDes<Chave, Item>::rank(Chave chave) {
    int contador = 0;
    noLista *aux;
    for (aux = cabeca->proximo; aux != nullptr; aux = aux->proximo) {
        if (strCmp(aux->chave, chave) < 0) contador++;
    }

    return contador;
}

template <class Chave, class Item>
Chave listaDes<Chave, Item>::seleciona(int k) {
    noLista *aux;
    
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
listaOrd<Chave, Item>::listaOrd(string nome_arquivo): cabeca(new noLista[1]) {
    cabeca->proximo = nullptr;
};

template <class Chave, class Item>
listaOrd<Chave, Item>::~listaOrd() {
    noLista *aux;

    while (cabeca != nullptr) {
        aux = cabeca->prox;
        delete [] cabeca;
        cabeca = aux;
    }

}

template <class Chave, class Item>
void listaOrd<Chave, Item>::insere(Chave chave, Item valor) {
    noLista *atual = cabeca->proximo, *anterior = cabeca;
    
    while (atual != nullptr) {
        if (strCmp(chave, atual->chave) == 0) {
            atual->chave = chave;
            return;
        }
        else if (strCmp(chave, atual->chave < 0)) break;
        
        anterior = atual;
        atual = atual->proximo;
    }

    anterior->proximo = new noLista[1];
    anterior->proximo->proximo = atual;
}

template <class Chave, class Item>
void listaOrd<Chave, Item>::remove(Chave chave) {
    noLista *atual = cabeca->proximo, *anterior = cabeca;
    int comparacao;
    while (atual != nullptr) {
        comparacao = strCmp(chave, atual->chave);
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
    noLista *atual = cabeca->proximo, *anterior = cabeca;
    int comparacao;
    while (atual != nullptr) {
        comparacao = strCmp(chave, atual->chave);
        if (comparacao == 0) {
            return Item;
        }
        else if (comparacao < 0) break;
        anterior = atual;
        atual = atual->proximo;
    }
    return nullptr;
}

template <class Chave, class Item>
int listaOrd<Chave, Item>::rank(Chave chave) {
    int contador = 0, comparacao;
    noLista *atual;
    while (atual != nullptr) {
        comparacao = strCmp(chave, atual->chave);
        if (comparacao == 0) break;
        else if (comparacao > 0) contador++;
    }
    return contador;
}

template <class Chave, class Item>
Chave listaOrd<Chave, Item>::seleciona(int k) {
    noLista *atual;
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
        excluiArvore(no->dir)
        excluiArvore(no->esq)
        delete [] no;
    }
}

template <class Chave, class Item>
void arvoreBin<Chave, Item>::insere(Chave chave, Item valor) {
    raiz = insereR(raiz, chave, valor);
}

template <class Chave, class Item>
noArvore<Chave, Item> arvoreBin<Chave, Item>::*insereR(noArvore<Chave, Item> *no, Chave chave, Item valor) {
    int comparacao;

    if (no == nullptr) {
        no = new noArvore[1];
        no->dir = nullptr;
        no->esq = nullptr;
        no->chave = chave;
        no->valor = valor;
        no->pai = nullptr;
    }
    else {
        comparacao = strCmp(no->chave, chave);
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
        comparacao = strCmp(no->chave, chave);
        if (comparacao == 0) 
            return no->valor;
        else if (comparacao > 0) 
            return devolveR(no->esq, chave);
        else 
            return devolveR(no->dir, chave)
    }
    return nullptr;
}

template <class Chave, class Item>
int arvoreBin<Chave, Item>::rank(Chave chave) {
    noArvore<Chave, Item> *no;
    no = raiz;
    int comparacao, contador = 0;
    while (no != nullptr) {
        comparacao = strCmp(no->chave, chave);
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
Chave arvoreBin<Chave, Item>::seleciona(int k) {}

template <class Chave, class Item>
void arvoreBin<Chave, Item>::remove(Chave chave){}

/*------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/*rank , remoção, seleção, etc* para chave inválida*/