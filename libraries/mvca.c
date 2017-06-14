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

int grafoDeterminadoNRotulo(int **matriz, int nVertice, int rotulosUsados[], int nRotulo, int rotuloAtual){
	/* Criamos um grafo*/
	Lista *grafo = (Lista*) malloc (sizeof(Lista));
	int i, j, k;

	/* Inicializamos um grafo */
	inicializarLista(grafo);

	/* Criamos o vértice */
	for(i = 0; i < nVertice; i++)
		inserirLista(grafo);

	removeVertice(grafo, 0);

	/* Inserimos arestas entre esse vértices*/
	for(i = 1; i < nVertice; i++){
		for(j = 1; j < nVertice; j++){
			for(k = 0; k < nRotulo; k++){
				if(rotulosUsados[k] == 2147483647){
					if(matriz[i][j] == k){
						insereAresta(grafo, i, j, false, matriz[i][j]);
					}	
				}
			}
			if(matriz[i][j] == rotuloAtual){
				insereAresta(grafo, i, j, false, matriz[i][j]);				
			}
		}
	}

	/* Contamos as componentes conectadas */
	return countComponenteConectadas(grafo);
	
}

void inicializaRotulosUsados(int rotulosUsados[], int nRotulo){
	int i;
	for(i = 0; i < nRotulo; i++)
		rotulosUsados[i] = 1;
}

int restaRotulosUsados(int rotulosUsados[], int nRotulo){
	int contador = 0, i;
	for(i = 0; i < nRotulo; i++){
		if(rotulosUsados[i] == 1)
			contador++;
	}
	return contador;
}

/**
* A função realizarMVCA em que recebemos a matriz de adjacência,
* número de vértices e número de rótulos. Retiramos da matriz
* valores da matrizes que são iguais, ao nmero de rótulo.
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
	int i, j, k;
	int rotulo, menor, componenteConectadas[nRotulo];
	int rotuloAtual, quantidadeRestantesRotulo, novoMenor;
	int rotulosUsados[nRotulo], resposta[nRotulo], novaComponenteConectadas[nRotulo];
		
	/* Procurar na matriz valores que tem o mesmo valor que o rótulo
	quando o valor é igual ao do rótulo não existe aresta */
	verificaMatriz(matriz, nVertice, nRotulo);

	/* Para cada rótulo montamos o grafo que possuem o mesmo rótulo */
	for(i = 0; i < nRotulo; i++){
		componenteConectadas[i] = grafoDeterminadoRotulo(matriz, nVertice, i);
		//printf("O rótulo %d e as quantidades de componentes conectadas %d.\n", i, componenteConectadas[i]);
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
			rotulo = i;
			//printf("O rótulo %d é que o possui o menor número de componentes conectadas.\n", i);
			break;
		}
	}

	/* Ou seja se eu tenho uma somente um componente conectada */
	if(menor == 1){
		printf("O rótulo %d tem %d componentes conectadas\n", rotulo, componenteConectadas[i]);
	} else {
		/* Quando eu tenho mais de uma componente conectada */
		/* Pegamos o que contém menos componentes conectadas e inserimos no vetor */
		rotuloAtual = rotulo;
		inicializaRotulosUsados(rotulosUsados, nRotulo);
		quantidadeRestantesRotulo = restaRotulosUsados(rotulosUsados, nRotulo);
		novoMenor = 0;
		j = 0;
		resposta[j++] = rotulo;
		while((novoMenor != 1) && (quantidadeRestantesRotulo > 0)){
			/* Se o rótulo atual é 9 coloco na posição 9 o valor 2147483647, ou seja, já foi utilizado */
			rotulosUsados[rotuloAtual] = 2147483647;
			novaComponenteConectadas[rotuloAtual] = 2147483647;
			
			/* Se tiver somente um valor faltando já adiciono ele*/
			if(restaRotulosUsados(rotulosUsados, nRotulo) == 1){
				for(i = 0; i < nRotulo; i++){
					if(rotulosUsados[i] == 1){
						resposta[j] = i;
					}
				}
				quantidadeRestantesRotulo = 0;
				break;
			}

			/* Então para posições diferentes de 2147483647 eu monto o grafo e conto suas componentes conectadas */
			for(i = 0; i < nRotulo; i++){
				if(rotulosUsados[i] < 2147483647){
					novaComponenteConectadas[i] = grafoDeterminadoNRotulo(matriz, nVertice, rotulosUsados, nRotulo, i);
				}
			}

			/* Verifico qual rótulo tem o menor componentes conectada */
			novoMenor = novaComponenteConectadas[0];
			//printf("Rótulo 0 - CC: %d\n", novaComponenteConectadas[0]);
			for(i = 1; i < nRotulo; i++){
				if(novaComponenteConectadas[i] < 2147483647){
					//printf("novaComponenteConectadas[%d] %d\n", i, novaComponenteConectadas[i]);
					//printf("novoMenor %d\n", novoMenor);
					if(novaComponenteConectadas[i] < novoMenor){
						novoMenor = novaComponenteConectadas[i];
						rotuloAtual = i;
					}				
				}
				//printf("Rótulo %d - CC: %d\n", i, novaComponenteConectadas[i]);
			}
			if(novoMenor == novaComponenteConectadas[0]){
				rotuloAtual = 0;
			}
			resposta[j] = rotuloAtual;
			j++;
			//printf("rotulo atual: %d\n", rotuloAtual);
			//printf("menor: %d\n", novoMenor);
			//printf("----------------\n");
		}
		for(i = 0; i < j; i++)
			printf("%d ", resposta[i]);
		printf("\n");

	}
	
	tempo = clock() - tempo;

	/* Retorna o tempo em segundos */
    double tempoGasto = ((double)tempo) / CLOCKS_PER_SEC; 
 
    return (tempoGasto * 1000000);
 
}