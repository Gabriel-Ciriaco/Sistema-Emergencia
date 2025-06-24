#ifndef EXIBICAO_H
#define EXIBICAO_H

#include "../../estruturas/bairro/bairro.h"
#include "../../estruturas/cidadao/cidadao.h"
#include "../../estruturas/profissional/profissional.h"

#include "../../estruturas/ocorrencia/ocorrencia.h"

#include "../../estruturas/tipos_abstratos/tabela_hash/tabela_hash.h"


void exibirCidadao(Cidadao cidadao);

void exibirProfissional(Profissional profissional);

void exibirOcorrencia(Ocorrencia ocorrencia);

void exibirHistoricoAtendimento(Profissional profissional);

void exibirTodosAtendimentos(TabelaHash * profissionais, int quantidadeProfissionais);


#endif // EXIBICAO_H
