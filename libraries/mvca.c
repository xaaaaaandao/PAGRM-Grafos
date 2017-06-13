#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mvca.h"

/**
* A função converterMatrizToLista em que recebemos a Lista, que representa
* o nosso grafo, matriz que é a matriz de adjacência, nVertice é a quantidade número de vértice,
* nRotulo é a quantidade rótulos. No qual pega a matriz de adjacência, e conveter para a lista
* que representa o grafo.
@param grafo, é um Lista* que contém o nosso grafo.
@param matriz, é um int** que contém a matriz de adjacência.
@param nVertice, é um int que contém a quantidade de vértices.
@param nRotulo, é um int que contém a quantidade de rótulos.
@return void, retorna nada.
*/
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

/**
* A função componenteConectadas em que recebemos a Lista, que representa
* o nosso grafo, e recebemos No que será o que será pintado
* e o nó que iremos verificar seu adjacante.
* Enfim, no final das contas essa função é uma busca profunidade.
@param l, é um Lista* que contém o nosso grafo.
@param no, é um No* que contém o nó que será verificado seus adjacentes.
@return void, retorna nada.
*/
void componenteConectadas(Lista *l, No *no) {
	tempo++;
	no -> tempoDescoberta = tempo;
	no -> cor = Cinza;
	No *auxiliar;
	noAdjacente *auxiliarAdjacente = no -> adjacente -> primeiro;
	while (auxiliarAdjacente != NULL) {
		auxiliar = getAdjacente(l, auxiliarAdjacente -> id);
		if (auxiliar -> cor == Branco) {
			auxiliar -> pai = no -> id;
			componenteConectadas(l, auxiliar);
		}
		auxiliarAdjacente = auxiliarAdjacente -> proximo;
	}
	no -> cor = Preto;
	tempo++;
	no -> tempoFinalizacao = tempo;
}

/**
* A função countComponenteConectadas em que recebemos a Lista, que representa
* o nosso grafo em que modificamos a inicialização da busca em profundidade 
* em que cada vez que reiniciamos a busca incrementamos nossa variável. 
@param l, é um Lista* que contém o nosso grafo.
@return contador, retorna inteiro que é a quantidade de componentes conectadas.
*/
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
			componenteConectadas(l, auxiliar);
		}
		auxiliar = auxiliar -> proximo;
	}	
	return contador;
}

/**
* A função verificaMatriz em que recebemos a matriz de adjacência,
* número de vértices em que verificamos se na posição
* da matriz é igual ao número máximo de rótulo, se for igual é que não existe a aresta.
@param matriz, é um inteiro que contém a matriz de adjacência.
@param nVertice, é um inteiro que contém a quantidade total de vértices.
@param nRotulo, é um inteiro que contém a quantidade total de rótulos.
@return void, retorna nada.
*/
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

/**
* A função imprimirMatriz em que recebemos a matriz de adjacência,
* número de vértices em que imprimimos cada uma das posições da matriz de adjacência.
@param matriz, é um inteiro que contém a matriz de adjacência.
@param nVertice, é um inteiro que contém a quantidade total de vértices.
@return void, retorna nada.
*/
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


/**
* A função grafoDeterminadoRotulo em que recebemos a matriz de adjacência,
* número de vértices e o rótulo atual. Adicionamos a quantidade vértices 
* existentes, e percorremos a matriz e quando achamos o valor do rótulo atual
* adicionamos a arestas. Após isso retornamos a quantidade de componentes 
* conetctadas para aquele determinado rótulo.
@param matriz, é um inteiro que contém a matriz de adjacência.
@param nVertice, é um inteiro que contém a quantidade total de vértices.
@param rotulo, é um inteiro que é o rótulo atual para se criar um grafo.
@return inteiro, retorna o a quantidade componentes conectadas daquele rótulo.
*/
int grafoDeterminadoRotulo(int **matriz, int nVertice, int rotulo){
	/* Criamos um grafo*/
	Lista *grafo = (Lista*) malloc (sizeof(Lista));
	int i, j;

	/* Inicializamos um grafo */
	inicializarLista(grafo);

	/* Criamos o vértice */
	for(i = 0; i < nVertice; i++)
		inserirLista(grafo);

	removeVertice(grafo, 0);

	/* Inserimos arestas entre esse vértices*/
	for(i = 1; i < nVertice; i++){
		for(j = 1; j < nVertice; j++){
			if(matriz[i][j] == rotulo){
				insereAresta(grafo, i, j, false, matriz[i][j]);
			}
		}
	}

	/* Contamos as componentes conectadas */
	return countComponenteConectadas(grafo);
	
}

/**
* A função realizarMVCA em que recebemos a matriz de adjacência,
* número de vértices e número de rótulos. Retiramos da matriz
* valores da matrizes que são iguais, ao número de rótulo.
* Após isso criamos o grafo para aquele determinado rótulo, 
* e depois contamos as componentes conectadas e por fim, imprimimos
* qual é o rótulo que possui menos componentes conectadas.
@param matriz, é um inteiro que contém a matriz de adjacência.
@param nVertice, é um inteiro que contém a quantidade total de vértices.
@param nRotulo, é um inteiro que contém a quantidade total de rótulos.
@return (tempoGasto * 1000000), retorna o tempo gasto para realizar o MVCA.
*/
double realizarMVCA(int **matriz, int nVertice, int nRotulo){
	clock_t tempo = clock();
	int i, componenteConectadas[nRotulo], menor;

	/* Procurar na matriz valores que tem o mesmo valor que o rótulo
	quando o valor é igual ao do rótulo não existe aresta */
	verificaMatriz(matriz, nVertice, nRotulo);

	/* Para cada rótulo montamos o grafo que possuem o mesmo rótulo */
	for(i = 0; i < nRotulo; i++){
		componenteConectadas[i] = grafoDeterminadoRotulo(matriz, nVertice, i);
		printf("O rótulo %d e as quantidades de componentes conectadas %d.\n", i, componenteConectadas[i]);
	}
	
	/* Verificamos qual é o menor rótulo que possui o menor número de componentes conectadas */
	menor = componenteConectadas[0];
	for(i = 1; i < nRotulo; i++){
		if(menor > componenteConectadas[i]){
			menor = componenteConectadas[i];
		}
	}

	for(i = 0; i < nRotulo; i++){
		if(menor == componenteConectadas[i]){
			printf("O rótulo %d é que o possui o menor número de componentes conectadas.\n", i);
			break;
		}
	}	
	
	tempo = clock() - tempo;

	/* Retorna o tempo em segundos */
    double tempoGasto = ((double)tempo) / CLOCKS_PER_SEC; 
 
    return (tempoGasto * 1000000);
 
}