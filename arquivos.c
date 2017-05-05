#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivos.h"


int preencheMatriz(int **matriz, char *linha){
	char peso[TAMANHO];
	int i = 0, j = 0, k = 0, valorPeso;
	while(linha[i] != '\0'){
		if(linha[i] == ' '){
			peso[j] = '\0';
			valorPeso = atoi(peso);
			printf("%d\n", numeroLinha);
			matriz[numeroLinha][k] = valorPeso;
//			printf("%d ", valorPeso);
			memset(peso, 0, sizeof(peso));
			j = 0;
			k++;
		} else {
			peso[j] = linha[i];
			j++;
		}
		i++;
	}
	printf("\n");
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

void lendoArquivo(char *name){
	char linha[TAMANHO];
	printf("lendo arquivo: %s\n", name);
	FILE *entrada = fopen(name, "r");
	int i = 0, j, k, nVertice, nRotulo;

	while(fgets(linha, sizeof(linha), entrada) != NULL){
		if(i == 0){
			nVertice = numeroVertice(linha);
			break;	
		}
	}

	int **matrizAdjacencia = (int**) malloc (nVertice * sizeof(int*));
	for(j = 0; j < nVertice; j++){
		matrizAdjacencia[i] = (int*) malloc (nVertice * sizeof(int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
 	}

 	for(j = 0; j < nVertice; j++){
		for(k = 0; k < nVertice; k++){
			matrizAdjacencia[j][k] = 0;
		}
	}	

	numeroLinha = nVertice - 1;

	while(fgets(linha, sizeof(linha), entrada) != NULL){
		if(i == 0){
			nRotulo = numeroRotulo(linha);
		} else {
			preencheMatriz(matrizAdjacencia, linha);
			numeroLinha++;
		}
		i++;
	}


 	for(j = 0; j < nVertice; j++){
		for(k = 0; k < nVertice; k++){
			printf("%d ", matrizAdjacencia[j][k]);
		}
		printf("\n");
	}	

	fclose(entrada);
}