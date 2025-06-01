#include "fila_prioridade.h"

#include <stdlib.h>

NoFilaPrioridade * criarNoFilaPrioridade(ValorFilaPrioridade valor)
{
    NoFilaPrioridade * novoNo = (NoFilaPrioridade *) malloc(sizeof(NoFilaPrioridade));

    novoNo->valor = valor;

    novoNo->ant = NULL;

    novoNo->prox = NULL;

    return novoNo;
}

FilaPrioridade criarFilaPrioridade()
{
    FilaPrioridade novaFila;

    novaFila.inicio = NULL;

    novaFila.fim = NULL;
}
