#include "simulacao.h"
#include "./geradores/geradores.h"
#include "./cadastramento/cadastro.h"
#include "../estruturas/tipos_abstratos/arvore_ABB/arvore_abb.h"

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

    novoSimulador.qtdMaximaOcorrenciasPorCiclo = QTD_MAX_OCORRENCIAS_CICLO;

    /* Inicialização das tabelas */
    novoSimulador.bairros = criarTabelaHash(HASH_BAIRRO);

    novoSimulador.cidadaos = criarTabelaHash(HASH_CIDADAO);

    novoSimulador.unidadesServico = criarTabelaHash(HASH_UNIDADE_SERVICO);

    novoSimulador.filaAtendimento = criarFilaPrioridade();

    novoSimulador.filaBombeiro = criarFilaPrioridade();

    novoSimulador.filaHospital = criarFilaPrioridade();

    novoSimulador.filaPolicia = criarFilaPrioridade();

    novoSimulador.filaSamu = criarFilaPrioridade();

    novoSimulador.ocorrenciasPorID = criarABB();

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
            int qtdOcorrenciasNoCiclo = rand() % simulador->qtdMaximaOcorrenciasPorCiclo + 1;

            for(int i=1; i <= qtdOcorrenciasNoCiclo; i++)
            {
                Cidadao vitima = gerarCidadao();
                Cidadao responsavel = gerarCidadao();

                cadastrarCidadao(&(simulador->cidadaos), vitima);
                cadastrarCidadao(&(simulador->cidadaos), responsavel);

                Cidadao * vitimaTabela = resgatarCadastroCidadao(&(simulador->cidadaos),
                                                                 vitima.id);

                Cidadao * responsavelTabela = resgatarCadastroCidadao(&(simulador->cidadaos),
                                                                      responsavel.id);

                Ocorrencia novaOcorrencia = gerarOcorrencia(simulador->tempoAtualSimulacao,
                                                            vitimaTabela, responsavelTabela);

                simulador->ocorrenciasPorID = inserirValorABB(simulador->ocorrenciasPorID, novaOcorrencia);

                printf("\n[%s]: Nova ocorrência: %s\n-Descrição: %s\n-Vítima: %s\n",
                        simulador->tempoAtualSimulacao,
                        novaOcorrencia.id,
                        novaOcorrencia.descricao,
                        novaOcorrencia.vitima->nome);

                if (novaOcorrencia.responsavel)
                {
                    printf("-Responsável: %s\n", novaOcorrencia.responsavel->nome);
                }

                switch(novaOcorrencia.gravidade)
                {
                    case GRAVIDADE_BAIXA:
                        printf("-Gravidade: Baixa\n");

                        break;

                    case GRAVIDADE_MEDIA:
                        printf("-Gravidade: Média\n");

                        break;

                    case GRAVIDADE_ALTA:
                        printf("-Gravidade: Alta\n");

                        break;
                }

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
        }


        if(!estaVaziaFilaP(&(simulador->filaAtendimento)))
        {
            ValorFilaPrioridade valor = removerValorFilaP(&(simulador->filaAtendimento));

            Ocorrencia ocorrencia = valor.ocorrencia;

            printf("\n[%s]: Ocorrência retirada da fila de atendimento: %s\n",
                   simulador->tempoAtualSimulacao, ocorrencia.id);

            switch(valor.ocorrencia.tipo)
            {
                case OCORRENCIA_BOMBEIRO:

                    if(valor.ocorrencia.gravidade == GRAVIDADE_MEDIA || valor.ocorrencia.gravidade == GRAVIDADE_ALTA)
                    {
                        inserirValorFilaPInicio(&(simulador->filaBombeiro), valor);
                    }
                    else
                    {
                        inserirValorFilaPFim(&(simulador->filaBombeiro), valor);
                    }

                    printf("\n[%s]: Ocorrência adicionada à fila de atendimento dos bombeiros: %s\n",
                           simulador->tempoAtualSimulacao,
                           valor.ocorrencia.id);
                    break;

                case OCORRENCIA_HOSPITAL:

                    if(valor.ocorrencia.gravidade == GRAVIDADE_MEDIA || valor.ocorrencia.gravidade == GRAVIDADE_ALTA)
                    {
                        inserirValorFilaPInicio(&(simulador->filaHospital), valor);
                    }
                    else
                    {
                        inserirValorFilaPFim(&(simulador->filaHospital), valor);
                    }

                    printf("\n[%s]: Ocorrência adicionada à fila de atendimento do hospital: %s\n",
                           simulador->tempoAtualSimulacao,
                           valor.ocorrencia.id);

                    break;

                case OCORRENCIA_POLICIA:

                    if(valor.ocorrencia.gravidade == GRAVIDADE_MEDIA || valor.ocorrencia.gravidade == GRAVIDADE_ALTA)
                    {
                        inserirValorFilaPInicio(&(simulador->filaPolicia), valor);
                    }
                    else
                    {
                        inserirValorFilaPFim(&(simulador->filaPolicia), valor);
                    }

                    printf("\n[%s]: Ocorrência adicionada à fila de atendimento da polícia: %s\n",
                           simulador->tempoAtualSimulacao,
                           valor.ocorrencia.id);

                    break;

            }
        }

        if(!estaVaziaFilaP(&(simulador->filaBombeiro)))
        {
            ValorFilaPrioridade valor = removerValorFilaP(&(simulador->filaBombeiro));

            Ocorrencia ocorrencia = valor.ocorrencia;

            printf("\n[%s]: Ocorrência retirada da fila do bombeiro: %s\n",
                   simulador->tempoAtualSimulacao, ocorrencia.id);

            /*
                TO-DO: realizar o tratamento da ocorrencia retirarda.
            */
        }

        if(!estaVaziaFilaP(&(simulador->filaHospital)))
        {
            ValorFilaPrioridade valor = removerValorFilaP(&(simulador->filaHospital));

            Ocorrencia ocorrencia = valor.ocorrencia;

            printf("\n[%s]: Ocorrência retirada da fila do hospital: %s\n",
                   simulador->tempoAtualSimulacao, ocorrencia.id);

            /*
                TO-DO: realizar o tratamento da ocorrencia retirarda.
            */

        }

        if(!estaVaziaFilaP(&(simulador->filaPolicia)))
        {
            ValorFilaPrioridade valor = removerValorFilaP(&(simulador->filaPolicia));

            Ocorrencia ocorrencia = valor.ocorrencia;

            printf("\n[%s]: Ocorrência retirada da fila da polícia: %s\n",
                   simulador->tempoAtualSimulacao, ocorrencia.id);

            /*
                TO-DO: realizar o tratamento da ocorrencia retirarda.
            */

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

bool alterarQuantidadeOcorrenciasCiclo(Simulador *simulador, int novaQtd)
{
    if(novaQtd <= 0) return false;

    simulador->qtdMaximaOcorrenciasPorCiclo = novaQtd;

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

    destruirABB(simulador->ocorrenciasPorID);

    return true;
}
