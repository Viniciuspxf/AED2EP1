
unit_test: util.o ep1.o unit_test.o
	g++ util.o ep1.o unit_test.o -o unit_test -lm

unit_test.o: util.hpp tabeladesimbolos.hpp unit_test.cpp
	g++ -Wall -g -O0 -c unit_test.cpp

ep1.o: tabeladesimbolos.hpp util.hpp ep1.cpp
	g++ -Wall -g -O0 -c ep1.cpp

util.o: util.hpp util.cpp
	g++ -Wall -g -O0 -c util.cpp
