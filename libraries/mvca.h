#ifndef MVCA_H
#define MVCA_H

/* Bibliotecas necessárias */
#include "busca.h"
#include "lista.h"
#include "arquivos.h"

/* Protótipo das funções */
void converterMatrizToLista(Lista*, int**, int, int);
void componenteConectadas(Lista*, No*);
int countComponenteConectadas(Lista*);
void verificaMatriz(int**, int, int);
void imprimirMatriz(int**, int);
int grafoDeterminadoRotulo(int**, int, int);
double realizarMVCA(int**, int, int);

#endif /* MVCA_H */
