#ifndef UTILIDADES_SISTEMA_H_INCLUDED
#define UTILIDADES_SISTEMA_H_INCLUDED

#include "../../simulacao.h"
#include "../../../constantes-sistema/constantes-sistema.h"
#include "../../../estruturas/tipos_abstratos/arvore_ABB/arvore_abb.h"
#include "../../../estruturas/ocorrencia/ocorrencia.h"
#include "../../../estruturas/tipos_abstratos/arvore_AVL/arvore_avl.h"
#include "../../../estruturas/tipos_abstratos/pilha/pilha.h"

void mensagemBoasVindas();

bool configurarSimulacao(Simulador *simulador);

Ocorrencia *buscarOcorrenciaPorID(Arvore *raiz, char const *idOcorrencia);

void exibirOcorrencia(Ocorrencia ocorrencia);

void relatorioOcorrencias(Arvore *raiz);

void listarOcorrenciasPorGravidade(No *raiz);

int rodarMenu();

void exibirCidadao(Cidadao *cidadao);

void exibirHistoricoAtendimentos(Pilha *pilha);

#endif // UTILIDADES_SISTEMA_H_INCLUDED
