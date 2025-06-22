#ifndef SIMULACAO_H
#define SIMULACAO_H

#include "./controle-de-tempo/controle-de-tempo.h"

#include "../estruturas/tipos_abstratos/tabela_hash/tabela_hash.h"
#include "../estruturas/tipos_abstratos/fila_prioridade/fila_prioridade.h"
#include "../estruturas/tipos_abstratos/arvore_ABB/arvore_abb.h"
#include "../estruturas/tipos_abstratos/pilha/pilha.h"

#include <stdbool.h>
#include <time.h>

#define MAX_TEMPO_SIMULACAO 100

#define TMP_CHEGADA_OCORRENCIA 10

#define TMP_MAXIMO_OCORRENCIA 20

#define QTD_BAIRROS 10

#define QTD_CIDADAOS 10

#define QTD_BOMBEIROS 10

#define QTD_HOSPITAIS 10

#define QTD_POLICIAS 10

#define QTD_SAMUS 10

#define QTD_MAX_OCORRENCIAS_CICLO 5

typedef enum tipoEntidadeSimulador
{
    ENTIDADE_BAIRRO,
    ENTIDADE_CIDADAO,
    ENTIDADE_BOMBEIRO,
    ENTIDADE_HOSPITAL,
    ENTIDADE_POLICIA,
    ENTIDADE_SAMU

} TipoEntidadeSimulador;

typedef struct simulador
{
    char inicioSimulacao[FORMATO_TEMPO]; // A hora de início da simulação.

    char tempoAtualSimulacao[FORMATO_TEMPO];

    int tempoSimulacao; // O tempo de simulação em segundos.

    int tempoSimulacaoMaximo;

    int tempoChegadaOcorrencia;

    int tempoMaximoOcorrencia; //Tempo máximo de espera da ocorrência.


    int quantidadeBairros;

    int quantidadeCidadaos;

    int quantidadeProfissionais;

    int quantidadeBombeiros;

    int quantidadeHospitais;

    int quantidadePolicias;

    int quantidadeSamus;

    int qtdMaximaOcorrenciasPorCiclo;


    TabelaHash bairros;

    TabelaHash cidadaos;

    TabelaHash profissionais;

    /*
    TO-DO: Talvez, criar hash para cada uma.

    TabelaHash bombeiros;

    TabelaHash hospitais;

    TabelaHash policia;

    TabelaHash samus;*/

    TabelaHash unidadesServico;

    FilaPrioridade filaAtendimento;

    FilaPrioridade filaBombeiro;

    FilaPrioridade filaHospital;

    FilaPrioridade filaSamu;

    FilaPrioridade filaPolicia;

    ArvoreABB *ocorrenciasPorID;

} Simulador;


Simulador criarSimulador();

bool rodarSimulacao(Simulador * simulador);

bool alterarTempoMaximoSimulacao(Simulador * simulador, int novoTempoMaximo);

bool alterarQuantidadeOcorrenciasCiclo(Simulador *simulador, int novaQtd);

bool alterarQuantidadeEntidade(Simulador * simulador,
                               TipoEntidadeSimulador entidade,
                               int novaQuantidade);

bool limparSimulacao(Simulador * simulador);

#endif // SIMULACAO_H
