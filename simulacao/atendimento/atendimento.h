#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

#include "../../estruturas/ocorrencia/ocorrencia.h"

#include "../../estruturas/bairro/bairro.h"

#include "../../estruturas/tipos_abstratos/lista_cruzada/lista_cruzada.h"
#include "../../estruturas/tipos_abstratos/tabela_hash/tabela_hash.h"
#include "../../estruturas/tipos_abstratos/fila_prioridade/fila_prioridade.h"


Bairro * procurarBairroProximo(ListaCruzada * bairrosUnidades,
                               TabelaHash * bairros,
                               Ocorrencia ocorrencia);

void inserirFilaGravidade(FilaPrioridade * filaP, Ocorrencia ocorrencia);

Ocorrencia removerOcorrenciaFila(FilaPrioridade * filaP);

void tratarFilaOcorrencia(FilaPrioridade * filaP,
                          const char * tempoSimulacao,
                          const char * nomeFila);

#endif // ATENDIMENTO_H
