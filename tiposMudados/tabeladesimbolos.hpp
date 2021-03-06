#include "util.hpp"
#include <string>
using namespace std;

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
class vetorDes {
    public:
        vetorDes(string nome_arquivo);
        ~vetorDes();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
class vetorOrd {
    public:
        vetorOrd(string nome_arquivo);
        ~vetorOrd();
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
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
class arvoreBin {
    private:
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
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
class treap {
    public:
        treap(string nome_arquivo);
        ~treap();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
class arvore23 {
    public:
        arvore23(string nome_arquivo);
        ~arvore23();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
class arvoreRN {
    public:
        arvoreRN(string nome_arquivo);
        ~arvoreRN();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
class hashTable {
    public:
        hashTable(string nome_arquivo);
        ~hashTable();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};