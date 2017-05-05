#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"
#include "lista.h"
#include "opcao.h"
#include "telas.h"

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