#ifndef UTILIDADES_SISTEMA_H
#define UTILIDADES_SISTEMA_H

#include "../../simulacao.h"

#include "../../../constantes-sistema/constantes-sistema.h"

#include "../../../estruturas/ocorrencia/ocorrencia.h"

#include "../../../estruturas/tipos_abstratos/arvore_ABB/arvore_abb.h"
#include "../../../estruturas/tipos_abstratos/arvore_AVL/arvore_avl.h"
#include "../../../estruturas/tipos_abstratos/pilha/pilha.h"

void mensagemBoasVindas();

int rodarMenu();

bool configurarSimulacao(Simulador *simulador);

Ocorrencia *buscarOcorrenciaPorID(ArvoreABB *raiz, char const *idOcorrencia);

void relatorioOcorrencias(ArvoreABB *raiz);

void listarOcorrenciasPorGravidade(No *raiz);

#endif // UTILIDADES_SISTEMA_H
