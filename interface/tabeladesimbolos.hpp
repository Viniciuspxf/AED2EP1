#include "util.hpp"
#include <string>
using namespace std;

template <class Chave, class Item>
class celula {
    public:
        Chave chave;
        Item valor;
};

template <class Chave, class Item>
class noLista {
    public:
        noLista *proximo;
        Chave chave;
        Item valor;
};

template <class Chave, class Item> 
class noArvore {
    public:
        noArvore *pai;
        noArvore *esq;
        noArvore *dir;
        Chave chave;
        Item valor;
};

template <class Chave, class Item> 
class noTreap {
    public:
        noTreap *pai;
        noTreap *esq;
        noTreap *dir;
        int prioridade;
        Chave chave;
        Item valor;
};

template <class Chave, class Item> 
class noRN {
    public:
        noRN *pai;
        noRN *esq;
        noRN *dir;
        int black;
        Chave chave;
        Item valor;
};

template <class Chave, class Item>
class no23 {
    public:
        bool tres;
        no23 *pai;
        no23 *esq;
        no23 *meio;
        no23 *dir;
        Chave chaveEsq;
        Chave chaveDir;
        Item valorEsq;
        Item valorDir;
};

template <class Chave, class Item>
class vetorDes {
    private:
        void resize();
        int n;
        int max;
        celula<Chave, Item> *vetor;
    public:
        vetorDes(string nome_arquivo);
        ~vetorDes();
        void printa();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
class vetorOrd {
    private:
        void resize();
        int n;
        int max;
        celula<Chave, Item> *vetor;
    public:
        vetorOrd(string nome_arquivo);
        ~vetorOrd();
        void printa();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
class listaDes {
    private:
        noLista<Chave, Item> *cabeca;
    public:
        listaDes(string nome_arquivo);
        ~listaDes();
        void printa();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
class listaOrd {
    private:
        noLista<Chave, Item> *cabeca;
    public:
        listaOrd(string nome_arquivo);
        ~listaOrd();
        void printa();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
class arvoreBin {
    private:
        void printaR(noArvore<Chave, Item> *no);
        noArvore<Chave, Item> * removeR(noArvore<Chave, Item> *no, Chave chave);
        noArvore<Chave, Item> * insereR(noArvore<Chave, Item> *no, Chave chave, Item valor);
        Chave selecionaR(noArvore<Chave, Item> *no, int k, int *contador);
        int contaNos(noArvore<Chave, Item> *no);
        Item devolveR(noArvore<Chave, Item> *no, Chave chave);
        void excluiArvore(noArvore<Chave, Item> *no);
        noArvore<Chave, Item> *raiz;
    public:
        arvoreBin(string nome_arquivo);
        ~arvoreBin();
        void printa();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
class treap {
    private:
        void printaR(noTreap<Chave, Item> *no);
        noTreap<Chave, Item> * removeR(noTreap<Chave, Item> *no, Chave chave);
        noTreap<Chave, Item> * insereR(noTreap<Chave, Item> *no, Chave chave, Item valor);
        Chave selecionaR(noTreap<Chave, Item> *no, int k, int *contador);
        int contaNos(noTreap<Chave, Item> *no);
        Item devolveR(noTreap<Chave, Item> *no, Chave chave);
        void excluiArvore(noTreap<Chave, Item> *no);
        noTreap<Chave, Item> *raiz;
    public:
        treap(string nome_arquivo);
        ~treap();
        void printa();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
class arvore23 {
    private:
        no23<Chave, Item> *raiz;
        int contaNos(no23<Chave, Item> *no);
        void printaR(no23<Chave, Item> *no);
    public:
        arvore23(string nome_arquivo);
        ~arvore23();
        void printa();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
class arvoreRN {
    private:
        void rotacionaEsq(noRN<Chave, Item> *no);
        void rotacionaDir(noRN<Chave, Item> *no);
        void printaR(noRN<Chave, Item> *no);
        void excluiArvore(noRN<Chave, Item> *no);
        int contaNos(noRN<Chave, Item> *no);
        Item devolveR(noRN<Chave, Item> *no, Chave chave);
        Chave selecionaR(noRN<Chave, Item> *no, int k, int *contador);
        noRN<Chave, Item> *raiz;
    public:
        arvoreRN(string nome_arquivo);
        ~arvoreRN();
        void printa();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
class hashTable {
    private:
        int m;
        noLista<Chave, Item> **table;
        int hash(Chave chave);
    public:
        hashTable(string nome_arquivo);
        ~hashTable();
        void printa();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};