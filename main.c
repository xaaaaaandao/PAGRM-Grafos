#include <stdio.h>
#include <stdlib.h>
#include "libraries/arquivos.h"
#include "libraries/lista.h"
#include "libraries/opcao.h"
#include "libraries/telas.h"

int main(int argc, char *argv[]){

	if(argc == 2){
		telaLimpa();
		lendoArquivo(argv[1]);
	} else if(argc > 2){
		printf("erro: %s arquivoentrada|nada\n", argv[0]);
	} else {
		Lista *l = (Lista*) malloc (sizeof(Lista));
		inicializarLista(l);
		telaLimpa();
		opcaoGrafo();
		opcaoGrafoPonderado();
		opcaoPrincipal(l);

	}
	return 0;
}