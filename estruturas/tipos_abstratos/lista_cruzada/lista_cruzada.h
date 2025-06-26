#ifndef LISTA_CRUZADA_H_INCLUDED
#define LISTA_CRUZADA_H_INCLUDED

#include "../../../constantes-sistema/constantes-sistema.h"

#include<stdbool.h>

#define NUM_COLUNAS 4

typedef enum tipoUnidadeServico{

    TUS_HOSPITAL,
    TUS_BOMBEIRO,
    TUS_POLICIA,
    TUS_SAMU,

}TipoUnidadeServico;

typedef struct noListaC
{

    char idBairro[MAX_ID];
    char idUnidadeServico[MAX_ID];

    int lin;
    int col;

    struct noListaC *proxLin;
    struct noListaC *proxCol;

}NoListaC;


typedef struct{

    NoListaC *vetorCol[NUM_COLUNAS];
    NoListaC *vetorLin[MAX_BAIRROS];

}ListaCruzada;

ListaCruzada criarListaCruzada();

NoListaC *criarNoListaCruzada(const char *idBairo, const char *idUnidadeServico, int lin, int col);

void inserirValorListaCruzada(ListaCruzada *listaC, TipoUnidadeServico tipo, const char *idBairro, const char *idUnidadeServico);

void removerValorListaCruzada(ListaCruzada *listaC, TipoUnidadeServico tipo, const char *idBairro);

NoListaC *buscarValorListaCruzada(ListaCruzada *listaC, TipoUnidadeServico tipo);

NoListaC *buscarBairroListaCruzada(ListaCruzada *listaC,
                                   TipoUnidadeServico tipo,
                                   const char *idBairro);

void destruirListaCruzada(ListaCruzada *listaC);

#endif // LISTA_CRUZADA_H_INCLUDED
