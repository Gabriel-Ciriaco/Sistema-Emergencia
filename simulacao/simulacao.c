#include "simulacao.h"
#include "./geradores/geradores.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


Simulador criarSimulador()
{
    Simulador novoSimulador;

    /* Inicialização dos tempos da simulação */

    novoSimulador.tempoSimulacao = 0;

    novoSimulador.tempoSimulacaoMaximo = MAX_TEMPO_SIMULACAO;

    novoSimulador.tempoChegadaOcorrencia = TMP_CHEGADA_OCORRENCIA;

    novoSimulador.tempoMaximoOcorrencia = TMP_MAXIMO_OCORRENCIA;


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

    novoSimulador.filaAtendimento = criarFilaPrioridade();

    novoSimulador.filaBombeiro = criarFilaPrioridade();

    novoSimulador.filaHospital = criarFilaPrioridade();

    novoSimulador.filaPolicia = criarFilaPrioridade();

    novoSimulador.filaSamu = criarFilaPrioridade();

    return novoSimulador;
}

bool rodarSimulacao(Simulador * simulador)
{
    calcularTempoAtual(simulador->inicioSimulacao);

    /*
        Inicializa uma seed para os eventos aleatórios.
    */
    srand(time(NULL));

    while (simulador->tempoSimulacao < simulador->tempoSimulacaoMaximo)
    {
        calcularTempoAtual(simulador->tempoAtualSimulacao);

        printf("\n[%s]: ** Simulando **\n", simulador->tempoAtualSimulacao);

        if(simulador->tempoSimulacao % simulador->tempoChegadaOcorrencia == 0)
        {
            Cidadao vitima = gerarCidadao();
            Cidadao responsavel = gerarCidadao();

            cadastrarCidadao(&(simulador->cidadaos), vitima);
            cadastrarCidadao(&(simulador->cidadaos), responsavel);

            Cidadao * vitimaTabela = resgatarCadastroCidadao(&(simulador->cidadaos), vitima.id);
            Cidadao * responsavelTabela = resgatarCadastroCidadao(&(simulador->cidadaos), responsavel.id);

            Ocorrencia novaOcorrencia = gerarOcorrencia(simulador->tempoAtualSimulacao, vitimaTabela, responsavelTabela);

            printf("\n[%s]: Nova ocorrência: %s\nVítima: %s\nResponsável: %s\n",
                   simulador->tempoAtualSimulacao,
                   novaOcorrencia.descricao,
                   novaOcorrencia.vitima->nome,
                   novaOcorrencia.responsavel->nome);

            ValorFilaPrioridade valor;

            valor.ocorrencia = novaOcorrencia;

            switch(novaOcorrencia.gravidade)
            {
                case GRAVIDADE_BAIXA:

                    inserirValorFilaPFim(&(simulador->filaAtendimento), valor);
                    break;

                case GRAVIDADE_MEDIA:
                case GRAVIDADE_ALTA:

                    inserirValorFilaPInicio(&(simulador->filaAtendimento), valor);
                    break;

            }

        }

        while(!estaVaziaFilaP(&(simulador->filaAtendimento)))
        {
            ValorFilaPrioridade valor = removerValorFilaP(&(simulador->filaAtendimento));

            Ocorrencia ocorrencia = valor.ocorrencia;

            printf("\n[%s]: Ocorrência retirada da fila de atedimento: %s\n",
                   simulador->tempoAtualSimulacao, ocorrencia.descricao);
        }

        simulador->tempoSimulacao++;

        sleep(1); // Espera 1 segundo.
    }

    return limparSimulacao(simulador);
}

bool alterarTempoMaximoSimulacao(Simulador * simulador, int novoTempo)
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

bool limparSimulacao(Simulador * simulador)
{
    limparTabela(&(simulador->bairros));
    limparTabela(&(simulador->cidadaos));
    limparTabela(&(simulador->unidadesServico));

    limparFilaPrioridade(&(simulador->filaAtendimento));
    limparFilaPrioridade(&(simulador->filaBombeiro));
    limparFilaPrioridade(&(simulador->filaHospital));
    limparFilaPrioridade(&(simulador->filaPolicia));
    limparFilaPrioridade(&(simulador->filaSamu));

    return true;
}
