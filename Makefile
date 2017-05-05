all:
	gcc arquivos.c -c
	gcc matriz.c -c
	gcc lista.c -c
	gcc telas.c -c
	gcc opcao.c -c
	gcc busca.c -c
	gcc fila.c -c
	gcc ordenacao.c -c
	gcc exercicios.c -c
	gcc componente.c -c
	gcc main.c -o main arquivos.o matriz.o lista.o telas.o opcao.o busca.o fila.o exercicios.o ordenacao.o componente.o
	./main

compile:
	gcc arquivos.c -c
	gcc matriz.c -c
	gcc lista.c -c
	gcc telas.c -c
	gcc opcao.c -c
	gcc busca.c -c
	gcc fila.c -c
	gcc ordenacao.c -c
	gcc exercicios.c -c
	gcc componente.c -c
	gcc main.c -o main arquivos.o matriz.o lista.o telas.o opcao.o busca.o fila.o exercicios.o ordenacao.o componente.o

up:
	git checkout master
	git pull origin master
	git merge xandao
	git push origin master
	git checkout xandao