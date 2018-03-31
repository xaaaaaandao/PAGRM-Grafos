all:
	cd libraries/ && gcc arquivos.c -c
	cd libraries/ && gcc matriz.c -c
	cd libraries/ && gcc lista.c -c
	cd libraries/ && gcc telas.c -c
	cd libraries/ && gcc opcao.c -c
	cd libraries/ && gcc busca.c -c
	cd libraries/ && gcc fila.c -c
	cd libraries/ && gcc ordenacao.c -c
	cd libraries/ && gcc exercicios.c -c
	cd libraries/ && gcc componente.c -c
	cd libraries/ && gcc mvca.c -c
	gcc main.c -o main libraries/arquivos.o libraries/matriz.o libraries/lista.o libraries/telas.o libraries/opcao.o libraries/busca.o libraries/fila.o libraries/exercicios.o libraries/ordenacao.o libraries/componente.o libraries/mvca.o
	./main

compile:
	cd libraries/ && gcc arquivos.c -c
	cd libraries/ && gcc matriz.c -c
	cd libraries/ && gcc lista.c -c
	cd libraries/ && gcc telas.c -c
	cd libraries/ && gcc opcao.c -c
	cd libraries/ && gcc busca.c -c
	cd libraries/ && gcc fila.c -c
	cd libraries/ && gcc ordenacao.c -c
	cd libraries/ && gcc exercicios.c -c
	cd libraries/ && gcc componente.c -c
	cd libraries/ && gcc mvca.c -c
	gcc main.c -o main libraries/arquivos.o libraries/matriz.o libraries/lista.o libraries/telas.o libraries/opcao.o libraries/busca.o libraries/fila.o libraries/exercicios.o libraries/ordenacao.o libraries/componente.o libraries/mvca.o

