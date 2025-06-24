#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

#include "../../estruturas/ocorrencia/ocorrencia.h"

#include "../../estruturas/tipos_abstratos/fila_prioridade/fila_prioridade.h"


void inserirFilaGravidade(FilaPrioridade * filaP, ValorFilaPrioridade valor);

void tratarFilaOcorrencia(FilaPrioridade * filaP,
                          const char * tempoSimulacao,
                          const char * nomeFila);

#endif // ATENDIMENTO_H
