#include <stdio.h>
#include <stdlib.h>
#include "busca.h"
#include "lista.h"

void converterMatrizToLista(Lista *grafo, int **matriz, int nVertice, int nRotulo){
	int i, j;
	for(i = 0; i < nVertice; i++)
		inserirLista(grafo);

	for(i = 1; i < nVertice; i++){
		for(j = 1; j < nVertice; j++){
			if(matriz[i][j] >= 0)
				insereAresta(grafo, i, j, false, matriz[i][j]);
		}
	}
}

void verificandoComponenteConectadas(Lista *l, No *no) {
	tempo++;
	no -> tempoDescoberta = tempo;
	no -> cor = Cinza;
	No *auxiliar;
	noAdjacente *auxiliarAdjacente = no -> adjacente -> primeiro;
	while (auxiliarAdjacente != NULL) {
		auxiliar = getAdjacente(l, auxiliarAdjacente -> id);
		if (auxiliar -> cor == Branco) {
			auxiliar -> pai = no -> id;
			verificandoComponenteConectadas(l, auxiliar);
		}
		auxiliarAdjacente = auxiliarAdjacente -> proximo;
	}
	no -> cor = Preto;
	tempo++;
	no -> tempoFinalizacao = tempo;
}

int countComponenteConectadas(Lista *l) {
	No *auxiliar = l -> primeiro;
	int contador = 0;
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
			verificandoComponenteConectadas(l, auxiliar);
		}
		auxiliar = auxiliar -> proximo;
	}	
	return contador;
}

void verificaMatriz(int **matriz, int nVertice, int nRotulo){
	int i, j;
	for(i = 1; i < nVertice; i++){
		for(j = 1; j < nVertice; j++){
			if(matriz[i][j] == nRotulo){
				matriz[i][j] = -1;
			}
		}
	}
}

void imprimirMatriz(int **matriz, int nVertice){
	int i, j;
	for(i = 0; i < nVertice; i++){
		for(j = 0; j < nVertice; j++){
			if(matriz[i][j] >= 0 && matriz[i][j] < 10){
				printf("0%d ", matriz[i][j]);
			} else {
				printf("%d ", matriz[i][j]);				
			}
		}
		printf("\n");
	}
	printf("\n");
}

int grafoDeterminadoRotulo(int **matriz, int nVertice, int rotulo){
	Lista *grafo = (Lista*) malloc (sizeof(Lista));
	int i, j;

	inicializarLista(grafo);

	for(i = 0; i < nVertice; i++)
		inserirLista(grafo);

	removeVertice(grafo, 0);

	for(i = 1; i < nVertice; i++){
		for(j = 1; j < nVertice; j++){
			if(matriz[i][j] == rotulo){
				insereAresta(grafo, i, j, false, matriz[i][j]);
			}
		}
	}

	return countComponenteConectadas(grafo);
	
}

void componenteConectadas(int **matriz, int nVertice, int nRotulo){
	Lista *grafo = (Lista*) malloc (sizeof(Lista));
	int i, componenteConectadas[nRotulo];
	
	inicializarLista(grafo);
	/* procurar na matriz valores que tem o mesmo valor que o rótulo
	quando o valor é igual ao do rótulo não existe aresta */
	verificaMatriz(matriz, nVertice, nRotulo);

	/* converte a matriz para a lista */
	converterMatrizToLista(grafo, matriz, nVertice, nRotulo);
	removeVertice(grafo, 0);

	for(i = 0; i < nRotulo; i++){
		componenteConectadas[i] = grafoDeterminadoRotulo(matriz, nVertice, i);
		printf("O número de componentes conectadas: %d\n", componenteConectadas[i]);
	}

}