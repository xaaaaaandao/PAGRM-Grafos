#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void converterMatrizToLista(Lista *grafo, int **matriz, int nVertice){
	int i, j;
	for(i = 0; i < nVertice; i++)
		inserirLista(grafo);

	for(i = 1; i < nVertice; i++){
		for(j = 1; j < nVertice; j++){
			if(matriz[i][j] > 0)
				insereAresta(grafo, i, j, false, matriz[i][j]);
		}
	}
}

void removeRotulo(){

}


void countComponenteConectadas(int **matriz, int nVertice, int nRotulo){
	Lista *grafo = (Lista*) malloc (sizeof(Lista));
	int i, j;
	int quantidadeComponenteConectadas[nRotulo];
	
	inicializarLista(grafo);
	quantidadeComponenteConectadas[0] = 0;

	converterMatrizToLista(grafo, matriz, nVertice);
	removeVertice(grafo, 0);
	imprimirLista(grafo);
	


	printf("\n");
	for(i = 0; i < nVertice; i++){
		for(j = 0; j < nVertice; j++){
			if(matriz[i][j] < 10)
				printf("0%d ", matriz[i][j]);
			else
				printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}

	//usar busca em profundidade
}