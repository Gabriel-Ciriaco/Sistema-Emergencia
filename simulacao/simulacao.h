#ifndef SIMULACAO_H
#define SIMULACAO_H

#include "../estruturas/tipos_abstratos/tabela_hash/tabela_hash.h"

#include <stdbool.h>
#include <time.h>

#define FORMATO_TEMPO 9

#define MAX_TEMPO_SIMULACAO 100

#define QTD_BAIRROS 10

#define QTD_CIDADAOS 10

#define QTD_BOMBEIROS 10

#define QTD_HOSPITAIS 10

#define QTD_POLICIAS 10

#define QTD_SAMUS 10

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


    int quantidadeBairros;

    int quantidadeCidadaos;

    int quantidadeBombeiros;

    int quantidadeHospitais;

    int quantidadePolicias;

    int quantidadeSamus;


    TabelaHash bairros;

    TabelaHash cidadaos;

    /*
    TO-DO: Talvez, criar hash para cada uma.

    TabelaHash bombeiros;

    TabelaHash hospitais;

    TabelaHash policia;

    TabelaHash samus;*/

    TabelaHash unidadesServico;

} Simulador;


Simulador criarSimulador();

bool rodarSimulacao(Simulador * simulador);

bool alterarTempoSimulacao(Simulador * simulador, int novoTempoMaximo);

bool alterarQuantidadeEntidade(Simulador * simulador,
                               TipoEntidadeSimulador entidade,
                               int novaQuantidade);

bool limparSimulacao(Simulador * simulador);

#endif // SIMULACAO_H
