#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#include "../../ocorrencia/ocorrencia.h"

#include "../../unidades-de-servico/unidadade-de-servico.h"

#include<stdbool.h>

typedef union valorFilaPrioridade
{
    Ocorrencia ocorrencia;

    UnidadeServico unidadeServico;

} ValorFilaPrioridade;

typedef struct noFilaPrioridade
{
    ValorFilaPrioridade valor;

    struct noFilaPrioridade * ant;

    struct noFilaPrioridade * prox;

} NoFilaPrioridade;

typedef struct filaPrioridade
{
    NoFilaPrioridade * inicio;

    NoFilaPrioridade * fim;

} FilaPrioridade;


NoFilaPrioridade * criarNoFilaPrioridade(ValorFilaPrioridade valor);

FilaPrioridade criarFilaPrioridade();

bool estaVaziaFilaP(FilaPrioridade *filaP);

void inserirValorFilaPInicio(FilaPrioridade * filaP,
                       ValorFilaPrioridade valor);

void inserirValorFilaPFim(FilaPrioridade * filaP,
                          ValorFilaPrioridade valor);

ValorFilaPrioridade removerValorFilaP(FilaPrioridade * filaP);

void limparFilaPrioridade(FilaPrioridade * filaP);


#endif // FILA_PRIORIDADE_H
