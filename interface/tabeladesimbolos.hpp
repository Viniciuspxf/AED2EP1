#include "util.hpp"

template <class Chave, class Item>
class vetorDes {
    public:
        vetorDes(String nome_arquivo);
        ~vetorDes();
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove(Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};