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

bool estaVaziaFilaP(FilaPrioridade * filaP)
{
    return (filaP->inicio == NULL) && (filaP->fim == NULL);
}

void inserirValorFilaPInicio(FilaPrioridade * filaP, ValorFilaPrioridade valor)
{
    NoFilaPrioridade *novoNo = criarNoFilaPrioridade(valor);

    if(estaVaziaFilaP(filaP))
    {
        filaP->inicio = novoNo;
        filaP->fim = novoNo;
    }

    novoNo->prox = filaP->inicio;
    filaP->inicio->ant = novoNo;
    filaP->inicio = novoNo;

}


void inserirValorFilaPFim(FilaPrioridade * filaP, ValorFilaPrioridade valor)
{
    NoFilaPrioridade *novoNo = criarNoFilaPrioridade(valor);

    if(estaVaziaFilaP(filaP))
    {
        filaP->inicio = novoNo;
        filaP->fim = novoNo;
    }

    filaP->fim->prox = novoNo;
    novoNo->ant = filaP->fim;
    filaP->fim = novoNo;
}


ValorFilaPrioridade removerValorFilaP(FilaPrioridade * filaP)
{
    if(estaVaziaFilaP(filaP))
    {
        //TODO: ver com o Gabriel o que será retornado aqui.
    }

    ValorFilaPrioridade valorRemovido = filaP->inicio->valor;
    NoFilaPrioridade *remover = filaP->inicio;

    if(filaP->inicio == filaP->fim)
    {
        filaP->inicio = NULL;
        filaP->fim = NULL;

    }else{

        filaP->inicio = filaP->inicio->prox;
        filaP->inicio->ant = NULL;

    }

    free(remover);

    return valorRemovido;
}

void limparFilaPrioridade(FilaPrioridade * filaP)
{
    if(estaVaziaFilaP(filaP))
    {
        return;
    }

    while(!estaVaziaFilaP(filaP))
    {
        removerValorFilaP(filaP);
    }
}
