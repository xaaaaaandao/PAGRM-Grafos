#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mvca.h"
#include "arquivos.h"

/**
* A função preencheMatriz em que recebemos a matriz de adjacência,
* e a linha do arquivo, em que percorremos a linha e inserimos cada um dos elementos da 
* linha na matriz de adjacência. 
@param matriz, é um inteiro que contém a matriz de adjacência.
@param linha, é um char que é a linha do arquivo.
@return void, retorna nada.
*/
void preencheMatriz(int **matriz, char *linha){
	char peso[TAMANHO];
	int i = 0, j = 0, k = 1, valorPeso;
	while(linha[i] != '\0'){
		if(linha[i] == ' '){
			peso[j] = '\0';
			valorPeso = atoi(peso);
			matriz[numeroLinha][k] = valorPeso;
			//matriz[k][numeroLinha] = valorPeso;
			memset(peso, 0, sizeof(peso));
			j = 0;
			k++;
			//printf("%d\n", k);
		} else {
			peso[j] = linha[i];
			j++;
		}
		i++;
	}
}

/**
* A função espacoBranco em que recebemos a linha do arquivo,
* em que percorremos a linha e identificamos a primieira recorrência do caractere espaço em
* branco e retornamos essa posição.
@param linha, é um char que é a linha do arquivo.
@return i, é um inteiro que retorna a posição do espaço em branco.
*/
int espacoBranco(char *linha){
	int i = 0;
	while(linha[i] != '\0'){
		if(linha[i] == ' '){
			return i;
		}
		i++;
	}
	return -1;
}

/**
* A função numeroVertice em que recebemos a linha do arquivo,
* em que percorremos a linha e identificamos o número de vértice.
@param linha, é um char que é a linha do arquivo.
@return atoi(valorVertice), é um inteiro que retorna a conversão do valor com a quantidade de vértice.
*/
int numeroVertice(char *linha){
	int i = 0, j = 0;
	char valorVertice[TAMANHO];
	while(linha[i] != '\0'){
		if(linha[i] == ' '){
			break;
		} else {
			valorVertice[j] = linha[i];
			j++;			
		}
		i++;
	}
	valorVertice[j] = '\0';
	return atoi(valorVertice);
}

/**
* A função numeroRotulo em que recebemos a linha do arquivo,
* em que percorremos a linha e identificamos o número de rótulo.
@param linha, é um char que é a linha do arquivo.
@return atoi(valorVertice), é um inteiro que retorna a conversão do valor com a quantidade de rótulos.
*/
int numeroRotulo(char *linha){
	int i = 0, j = 0, espaco = espacoBranco(linha);
	char valorRotulo[TAMANHO];
	while(linha[i] != '\0'){
		if(i > espaco){
			valorRotulo[j] = linha[i];
			j++;
		}
		i++;
	}
	valorRotulo[j] = '\0';
	return atoi(valorRotulo);
}

/**
* A função lendoArquivo em que recebemos o nome do arquivo
* em que abrimos o arquivo, e extraímos os números de vértices, número de rótulos
* e por fim executamos o MVCA, imprimimos a média de rótulos e o tempo total.
@param name, é um char que é o nome do arquivo.
@return void, retorna nada.
*/
void lendoArquivo(char *name){
	double tempoGasto = 0;
	double media = 0;
	char linha[TAMANHO];
	double tempoTotal = 0;
	FILE *entrada = fopen(name, "r");
	int i = 0, j, k, nVertice, nRotulo, matrizAtual = 1;

	if(entrada == NULL){
		printf("\033[1m\033[31mnão existe o arquivo %s\033[0m\n", name);
		exit(1);
	}

	printf("\033[1m\033[32mlendo arquivo: %s\033[0m\n", name);
	
	/* pegar o número de vértices e rótulos */
	while(fgets(linha, sizeof(linha), entrada) != NULL){
		if(i == 0){
			nVertice = numeroVertice(linha) + 1;
			nRotulo = numeroRotulo(linha);
			break;	
		}
	}

	/* aloca matriz */
	int **matrizAdjacencia = (int**) malloc (nVertice * sizeof(int*));
	for(j = 0; j < nVertice; j++){
		matrizAdjacencia[j] = (int*) malloc (nVertice * sizeof(int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
 	}

 	/* inicializa matriz */
 	for(j = 0; j < nVertice; j++){
		for(k = 0; k < nVertice; k++){
			matrizAdjacencia[j][k] = -1;
		}
	}	

	numeroLinha = nVertice - 1;

	for(i = 1; i <= numeroLinha; i++)
		matrizAdjacencia[0][i] = i;
	
	for(i = 1; i <= numeroLinha; i++)
		matrizAdjacencia[i][0] = i;
	
	/* pecorre o arquivo e coloca na matriz */
	i = 0;
	while(fgets(linha, sizeof(linha), entrada) != NULL){
		if(i >= 0){
			preencheMatriz(matrizAdjacencia, linha);
			if(numeroLinha == 1){
				printf("\033[1m\033[32mlendo matriz [%d/10]\033[0m\n", matrizAtual);	
				clock_t tempo = clock();
				media = media + realizarMVCA(matrizAdjacencia, nVertice, nRotulo);
				tempo = clock() - tempo;
				tempoGasto = tempoGasto + (((double)tempo) / CLOCKS_PER_SEC); 
				matrizAtual++;
				numeroLinha = nVertice - 1;		
			} else {
				numeroLinha--;
			}
		}
		i++;
	}

	fclose(entrada);
	/* Tempo gasto vem em segundos e vezes 1000 para transformar em milisegundos */
	tempoGasto = tempoGasto * 1000;
	printf("\033[1m\033[32m=========================\033[0m\n");	
	printf("\033[1m\033[32m        RESULTADOS       \033[0m\n");	
	printf("\033[1m\033[32m=========================\033[0m\n");	
	printf("\033[1m\033[35mTempo total de execução:\033[0m %.2f ms\n", tempoGasto);
	printf("\033[1m\033[35mMédia dos rótulos:\033[0m %.2f\n", media/10);
}
