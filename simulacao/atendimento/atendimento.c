#include "atendimento.h"

#include <stdio.h>
#include <stdlib.h>


void inserirFilaGravidade(FilaPrioridade * filaP, Ocorrencia ocorrencia)
{
    ValorFilaPrioridade valor;

    valor.ocorrencia = ocorrencia;

    if (ocorrencia.gravidade == GRAVIDADE_MEDIA ||
        ocorrencia.gravidade == GRAVIDADE_ALTA)
    {
        inserirValorFilaPInicio(filaP, valor);
    }
    else
    {
        inserirValorFilaPFim(filaP, valor);
    }
}

Ocorrencia removerOcorrenciaFila(FilaPrioridade * filaP)
{
    ValorFilaPrioridade valor = removerValorFilaP(filaP);

    return valor.ocorrencia;
}

void tratarFilaOcorrencia(FilaPrioridade * filaP,
                          const char * tempoSimulacao,
                          const char * nomeFila)
{
    if (!estaVaziaFilaP(filaP))
    {
        ValorFilaPrioridade valor = removerValorFilaP(filaP);

        printf("\n[%s]: Ocorrência retirada da fila de %s: %s\n",
                tempoSimulacao, nomeFila, valor.ocorrencia.id);

    }
}
