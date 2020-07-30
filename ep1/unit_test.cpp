/*
 * MAC0323 Algoritmos e Estruturas de Dados II
 * 
 * Contador de frequencia de palavras em um texto
 *
 *     http://www.ime.usp.br/~pf/mac0122-2003/aulas/symb-table.html
 * 
 * AVISO: Este programa quebra se o conjunto de caracters nao 
 *        for de 7-bits ASCII, ou seja, textos iso-latin 8859-1
 *        com acentos, cedilha, ... fazem o programa quebrar.
 *        UTF-8 nem pensar.
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <sstream>
#include <time.h>
using namespace std;

#include "util.hpp"    /* emalloc(), ecalloc(), strCmp(), getLine(), stringCopy(), 
//                         ERRO(), AVISO(), getLine() */

/* tabela de símbolos */
#include "tabeladesimbolos.hpp"  /* devolve(), insere(), remove(), ... */

#define PROMPT      cout << ">>> ";
#define MIN_ST      "minST"
#define DELMIN_ST   "delminST"
#define GET_ST      "getST"
#define RANK_ST     "rankST"
#define DELETE_ST   "deleteST"
#define SELECT_ST   "selectST"

/*---------------------------------------------------------------*/
/*
 *  P R O T Ó T I P O S
 */
static void 
mostreUso (char *nomePrograma);

template <class ST>
void 
testeOperacoes(ST st);

/*---------------------------------------------------------------*/
/* 
 *  M A I N 
 */
int 
main(int argc, char *argv[])
{
    fstream arqTexto;

    if (argc < 3) mostreUso(argv[0]);

    /* abra arquivo com texto */
    arqTexto.open(argv[1]);

    if (arqTexto.fail()) {
        cout << "ERRO: arquivo" << argv[1] << "nao pode ser aberto.\n";
        exit(EXIT_FAILURE);
    }

    arqTexto.close();

    string nome_arquivo = argv[1];
    string tipo = argv[2];

    /* crie a ST*/
    cout << "criando ST...\n";

    /* usadas para medir tempo de processamento */
    clock_t start, end; 
    double elapsed = 0;

    if (tipo == "VD"){
        start = clock(); 
        vetorDes<string, int> *st = new vetorDes<string, int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
		delete st;
    }
    else if (tipo == "VO"){
        start = clock(); 
        vetorOrd<string, int> *st = new vetorOrd<string, int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
		delete st;
    }
    else if (tipo == "LD"){
        start = clock(); 
        listaDes<string, int> *st = new listaDes<string, int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
		delete st;
    }
    else if (tipo == "LO"){
        start = clock(); 
        listaOrd<string, int> *st = new listaOrd<string, int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
		delete st;
    }
    else if (tipo == "AB"){
        start = clock(); 
        arvoreBin<string, int> *st = new arvoreBin<string, int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
		delete st;
    }
    else if (tipo == "TR"){
        start = clock(); 
        treap<string, int> *st = new treap<string, int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
		delete st;
    }
    else if (tipo == "A23"){
        start = clock(); 
        arvore23<string, int> *st = new arvore23<string, int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
		delete st;
    }
    else if (tipo == "RN"){
        start = clock(); 
        arvoreRN<string, int> *st = new arvoreRN<string, int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
		delete st;
    }
    else if (tipo == "HS"){
        start = clock(); 
        hashTable<string, int> *st = new hashTable<string, int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
		delete st;
    }
    else {
        cout << "A estrutura" << tipo << "não é válida";
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

/*-------------------------------------------------------*/
/* 
 *  TESTEOPEARCOES(ST) 
 *
 *  RECEBE uma tabela de símbolos ST e testa várias operações
 *  interativamente.
 *
 *  A função supõe que as chaves são do tipo String e os
 *  valores são do tipo Integer (ver util.h).
 */
template <class ST>
void 
testeOperacoes(ST st)
{
    clock_t start, end; 
    double elapsed = 0;
    string linha;
    /* mostre uso */
    cout << "Possiveis operacoes do teste interativo:\n";
    cout << "minST, delminST, getST <chave>; rankST <chave>, deleteST <chave>, selectST <int>\n";
    cout << "CRTL-D para encerrar.\n";
    PROMPT;
    while (getline(cin, linha)) {
        /* pegue operacao a ser testada */
        string operacao;
        stringstream stream(linha);
        if (!(stream >> operacao)) {
            ERROR(operacao esperada);
        }
        /*---------------------------------*/
        else if (operacao == MIN_ST) {
            start = clock();
            string key = st->seleciona(0);
            end = clock();
            elapsed = (double (end - start)/ CLOCKS_PER_SEC);

            if (key == "") {
                cout << "ST vazia\n";
            } else {
                cout << key << "\n";
            }
            cout << "minST executado em " << elapsed << " segundos." << endl;
        }
        /*---------------------------------*/
        else if (operacao == DELMIN_ST) {
            start = clock();
            string key = st->seleciona(0);
            
            if (key == "") {
                cout << "ST já está vazia\n";
            } else {
                cout << "\"" << key; 
                st->remove(key);
                cout << "\" foi removida\n";
            }
            end = clock();
            elapsed = (double (end - start)/ CLOCKS_PER_SEC);
            cout << "delminST executado em " << elapsed << " segundos." << endl;
        }
        /*---------------------------------*/
        else if (operacao == "printST") {
            st->printa();
        }
        /*---------------------------------*/
        else {
            /* operaÃ§Ã£o necessita de argumento key */
            string key;
            if (!(stream >> key)) {
                ERROR(operacao necessita uma palavra);
            }
            /*---------------------------------*/
            else if (operacao == GET_ST) {
                int frequencia = -1;
                start = clock();
                frequencia = st->devolve(key); /* consulte a ST */
                end = clock();
                elapsed = (double (end - start)/ CLOCKS_PER_SEC);
                /* mostre o resultado da consulta */
                if (frequencia == -1) {
                    cout << key << ": 0\n";
                } else {
                    cout << key << ": " << frequencia << "\n";
                }
                cout << "getST executado em " << elapsed << " segundos." << endl;
            }
            /*---------------------------------*/
            else if (operacao == RANK_ST) {
                start = clock();
                int r = st->rank(key);
                end = clock();
                elapsed = (double (end - start)/ CLOCKS_PER_SEC);
                cout << r << "\n";
                cout << "rankST executado em " << elapsed << " segundos." << endl;
            }
            /*---------------------------------*/
            else if (operacao == DELETE_ST) {
                start = clock();                
                st->remove(key);
                end = clock();
                elapsed = (double (end - start)/ CLOCKS_PER_SEC);             
                cout << "\"" << key << "\" foi removida\n";
                cout << "deleteST executado em " << elapsed << " segundos." << endl;
            }
            else if (operacao == SELECT_ST) {
                int pos = stoi(key);
                start = clock();
                string chave = st->seleciona(pos);
                end = clock();
                elapsed = (double (end - start)/ CLOCKS_PER_SEC); 
                cout << "Posição " << pos << " = " << chave << "\n";
                cout << "selectST executado em " << elapsed << " segundos." << endl;
            }
            else if (operacao == "insertST") {
                int valor;
                if (!(stream >> valor)) {
                    ERROR(operacao necessita um numero);
                }
                else {
                    start = clock();
                    st->insere(key, valor);
                    end = clock();
                    elapsed = (double (end - start)/ CLOCKS_PER_SEC);
                    cout << "insertST executado em " << elapsed << " segundos." << endl;
                }
            }
            else {
                ERROR(operacao nao reconhecida);
            }
        }
        PROMPT;
    }
    cout << "\n";
}


/*-----------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S
 *                 A U X I L I A R E S 
 */
static void 
mostreUso (char *nomePrograma)
{
    cout << "Uso \n"
	     << "prompt> " << nomePrograma << " nome-arquivo tipo-tabela\n"
	     << "    nome-arquivo = nome do arquivo com o texto\n"
         << "    tipo-tabela  = sigla de estrutura que deve ser usada\n";
    exit(EXIT_FAILURE);
}   