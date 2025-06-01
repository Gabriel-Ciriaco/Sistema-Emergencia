#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#include "../../ocorrencia/ocorrencia.h"

#include "../../unidades-de-servico/unidadade-de-servico.h"


typedef union valorFilaPrioridade
{
    Ocorrencia * ocorrencia;

    UnidadeServico * unidadeServico;

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

void inserirValorFilaP(FilaPrioridade * filaP,
                       ValorFilaPrioridade valor);

ValorFilaPrioridade removerValorFilaPInicio(FilaPrioridade * filaP);

ValorFilaPrioridade removerValorFilaPFim(FilaPrioridade * filaP);

void limparFilaPrioridade(FilaPrioridade * filaP);

#endif // FILA_PRIORIDADE_H
