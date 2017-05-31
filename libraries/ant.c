#include <stdio.h>
#include <stdlib.h>
#include "busca.h"
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

int countComponenteConectadas(Lista *l) {
	No *auxiliar = l -> primeiro;
	int contador = 0;
	bool ciclico;
	while(auxiliar != NULL){
		auxiliar -> cor = Branco;
		auxiliar -> tempoDescoberta = -1;
		auxiliar -> tempoFinalizacao = -1;
		auxiliar -> pai = -1;
		auxiliar = auxiliar -> proximo;
	}
	auxiliar = l -> primeiro;
	while(auxiliar != NULL){
		if (auxiliar -> cor == Branco){
			contador++;
			ciclico = BuscaEmProfundidade(l, auxiliar);
		}
		auxiliar = auxiliar -> proximo;
	}	
	return contador;
}

void executaTeste(){
	int j, k;
	int **matrizAdjacencia = (int**) malloc (6 * sizeof(int*));
	for(j = 0; j < 6; j++){
		matrizAdjacencia[j] = (int*) malloc (6 * sizeof(int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
 	}

	for(j = 0; j < 6; j++){
		for(k = 0; k < 6; k++){
			matrizAdjacencia[j][k] = 0;
		}
	}

	//matrizAdjacencia[1][3] = 3;
	matrizAdjacencia[4][1] = 1;
	matrizAdjacencia[4][2] = 1;
	matrizAdjacencia[4][5] = 1;
	//matrizAdjacencia[5][1] = 1;
	
	Lista *grafo = (Lista*) malloc (sizeof(Lista));
	converterMatrizToLista(grafo, matrizAdjacencia, 6);
	imprimirLista(grafo);
	removeVertice(grafo, 0);
	printf("O número de componente conectadas: %d\n", countComponenteConectadas(grafo));
}

Lista *criaGrafo(int **matriz, int nVertice, int rotulo){
	Lista *grafo;
	limpaTodasLista(grafo);
	int i, j;

	for(i = 0; i < nVertice; i++)
		inserirLista(grafo);

	for(i = 1; i < nVertice; i++){
		for(j = 1; j < nVertice; j++){
			if(matriz[i][j] == rotulo){
				insereAresta(grafo, i, j, false, rotulo);
			}
		}
	}

	return grafo;
}



void componenteConectadas(int **matriz, int nVertice, int nRotulo){
	Lista *grafo = (Lista*) malloc (sizeof(Lista));
	int i, j;
	
	inicializarLista(grafo);
	converterMatrizToLista(grafo, matriz, nVertice);
	removeVertice(grafo, 0);

	/*for(i = 0; i <= nRotulo){
		auxiliar = criaGrafo(i);
	}*/

	//executaTeste();
	//printf("O número de componente conectadas: %d\n", countComponenteConectadas(grafo));
//	imprimirLista(grafo);
	
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