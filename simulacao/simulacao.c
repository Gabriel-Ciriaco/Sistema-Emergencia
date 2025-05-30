#include "simulacao.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


Simulador criarSimulador()
{
    Simulador novoSimulador;

    /* Inicialização dos tempos da simulação */

    novoSimulador.tempoSimulacao = 0;

    novoSimulador.tempoSimulacaoMaximo = MAX_TEMPO_SIMULACAO;


    /* Inicialização das quantidades */
    novoSimulador.quantidadeBairros = QTD_BAIRROS;

    novoSimulador.quantidadeCidadaos = QTD_CIDADAOS;

    novoSimulador.quantidadeBombeiros = QTD_BOMBEIROS;

    novoSimulador.quantidadeHospitais = QTD_HOSPITAIS;

    novoSimulador.quantidadePolicias = QTD_POLICIAS;

    novoSimulador.quantidadeSamus = QTD_SAMUS;

    /* Inicialização das tabelas */
    novoSimulador.bairros = criarTabelaHash(HASH_BAIRRO);

    novoSimulador.cidadaos = criarTabelaHash(HASH_CIDADAO);

    novoSimulador.unidadesServico = criarTabelaHash(HASH_UNIDADE_SERVICO);

}

bool rodarSimulacao(Simulador * simulador)
{
    time_t t = time(NULL);

    struct tm horaAtual = *localtime(&t);

    strftime(simulador->inicioSimulacao, FORMATO_TEMPO, "%H:%M:%S", &horaAtual);

    /*
        Inicializa uma seed para os eventos aleatórios.
    */
    srand(t);

    printf("\n[%s]: ** Simulação iniciada **\n", simulador->inicioSimulacao);

    while (simulador->tempoSimulacao < simulador->tempoSimulacaoMaximo)
    {
        time_t t = time(NULL);

        struct tm horaAtual = *localtime(&t);


        strftime(simulador->tempoAtualSimulacao, FORMATO_TEMPO, "%H:%M:%S", &horaAtual);

        printf("\n[%s]: ** Simulando... **\n", simulador->tempoAtualSimulacao);

        /*
            TO-DO: Adicionar a simulação em si.
        */

        char nome[MAX_NOME];

        nomeCidadaoAleatorio(nome);

        printf("\n** Nome aleatório: %s**\n", nome);

        simulador->tempoSimulacao++;

        sleep(1); // Espera 1 segundo.
    }

    return true;
}

bool alterarTempoSimulacao(Simulador * simulador, int novoTempo)
{
    if (novoTempo < 0) return false;

    simulador->tempoSimulacaoMaximo = novoTempo;

    return true;
}

bool alterarQuantidadeEntidade(Simulador * simulador,
                               TipoEntidadeSimulador entidade,
                               int novaQuantidade)
{
    if (novaQuantidade < 0) return false;

    switch (entidade)
    {
        case ENTIDADE_BAIRRO:
            simulador->quantidadeBairros = novaQuantidade;
            return true;

        case ENTIDADE_CIDADAO:
            simulador->quantidadeCidadaos = novaQuantidade;
            return true;

        case ENTIDADE_BOMBEIRO:
            simulador->quantidadeBombeiros = novaQuantidade;
            return true;

        case ENTIDADE_HOSPITAL:
            simulador->quantidadeHospitais = novaQuantidade;
            return true;

        case ENTIDADE_POLICIA:
            simulador->quantidadePolicias = novaQuantidade;
            return true;

        case ENTIDADE_SAMU:
            simulador->quantidadeSamus = novaQuantidade;
            return true;

        default:
            return false;
    }
}
