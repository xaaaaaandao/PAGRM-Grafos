#ifndef ARQUIVOS_H
#define	ARQUIVOS_H

/* Definido alguns valores */
#define TAMANHO 3276

/* Variáveis globais */
int numeroLinha;

/* Protótipos das funções */
void preencheMatriz(int **matriz, char *linha);
int espacoBranco(char*);
int numeroVertice(char*);
int numeroRotulo(char*);
void lendoArquivo(char*);

#endif /* ARQUIVOS_H */