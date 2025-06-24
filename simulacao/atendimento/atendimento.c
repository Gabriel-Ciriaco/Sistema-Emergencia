#include "atendimento.h"

#include <stdlib.h>


void inserirFilaGravidade(FilaPrioridade * filaP, ValorFilaPrioridade valor)
{
    if (valor.ocorrencia.gravidade == GRAVIDADE_MEDIA ||
        valor.ocorrencia.gravidade == GRAVIDADE_ALTA)
    {
        inserirValorFilaPInicio(filaP, valor);
    }
    else
    {
        inserirValorFilaPFim(filaP, valor);
    }
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
