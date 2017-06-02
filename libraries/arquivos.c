#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ant.h"
#include "arquivos.h"


int preencheMatriz(int **matriz, char *linha){
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

void inicializaMatriz(int **matriz, int nVertice){
	int i, j;
	int numeroLinha;
	for(i = 0; i < nVertice; i++){
		for (j = 0; j < nVertice; j++){
			matriz[i][j] = -1;
		}
	}

	numeroLinha = nVertice - 1;

	for(i = 1; i <= numeroLinha; i++)
		matriz[0][i] = i;
	
	for(i = 1; i <= numeroLinha; i++)
		matriz[i][0] = i;
	
}

void lendoArquivo(char *name){
	char linha[TAMANHO];
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
	
	/* pecorre o arquivo e coloca na matriz*/
	i = 0;
	while(fgets(linha, sizeof(linha), entrada) != NULL){
		if(i >= 0){
			preencheMatriz(matrizAdjacencia, linha);
			if(numeroLinha == 1){
				printf("\033[1m\033[32mlendo matriz [%d/10]\033[0m\n", matrizAtual);	
				componenteConectadas(matrizAdjacencia, nVertice, nRotulo);
				matrizAtual++;
				numeroLinha = nVertice - 1;		
			} else {
				numeroLinha--;
			}
		}
		i++;
	}

	fclose(entrada);
}