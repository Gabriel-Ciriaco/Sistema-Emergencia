#include "simulacao.h"

#include "./geradores/geradores.h"
#include "./cadastramento/cadastro.h"
#include "./atendimento/atendimento.h"
#include "./exibicao/exibicao.h"

#include "../estruturas/bairro/bairro.h"
#include "../estruturas/cidadao/cidadao.h"
#include "../estruturas/profissional/profissional.h"
#include "../estruturas/ocorrencia/ocorrencia.h"

#include "../estruturas/unidades-de-servico/bombeiro/bombeiro.h"
#include "../estruturas/unidades-de-servico/hospital/hospital.h"
#include "../estruturas/unidades-de-servico/policia/policia.h"
#include "../estruturas/unidades-de-servico/unidadade-de-servico.h"

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

    novoSimulador.quantidadeProfissionais = QTD_PROFISSIONAIS;

    novoSimulador.quantidadeBombeiros = QTD_BOMBEIROS;

    novoSimulador.quantidadeHospitais = QTD_HOSPITAIS;

    novoSimulador.quantidadePolicias = QTD_POLICIAS;

    novoSimulador.quantidadeSamus = QTD_SAMUS;

    novoSimulador.qtdMaximaOcorrenciasPorCiclo = QTD_MAX_OCORRENCIAS_CICLO;

    /* Inicialização das tabelas */
    novoSimulador.bairros = criarTabelaHash(HASH_BAIRRO);

    novoSimulador.cidadaos = criarTabelaHash(HASH_CIDADAO);

    novoSimulador.profissionais = criarTabelaHash(HASH_PROFISSIONAL);

    novoSimulador.bombeiros = criarTabelaHash(HASH_UNIDADE_SERVICO);

    novoSimulador.hospitais = criarTabelaHash(HASH_UNIDADE_SERVICO);

    novoSimulador.policias = criarTabelaHash(HASH_UNIDADE_SERVICO);

    /* Inicialização da Lista Cruzada  */

    novoSimulador.bairroUnidade = criarListaCruzada();

    /*Inicialização das filas*/
    novoSimulador.filaAtendimento = criarFilaPrioridade();

    novoSimulador.filaBombeiro = criarFilaPrioridade();

    novoSimulador.filaHospital = criarFilaPrioridade();

    novoSimulador.filaPolicia = criarFilaPrioridade();

    novoSimulador.filaSamu = criarFilaPrioridade();

    /*Inicialização das Árvores*/
    novoSimulador.ocorrenciasPorID = criarABB();

    novoSimulador.ocorrenciasPorGravidade = criarArvoreAvl();

    return novoSimulador;
}

bool criarEntidades(Simulador * simulador)
{
    // Cria profissionais
    for (int i = 0; i < simulador->quantidadeProfissionais; i++)
    {
        Profissional novoProfissional = gerarProfissional();

        cadastrarProfissional(&(simulador->profissionais), novoProfissional);
    }

    // Cria bairros.
    Bairro  * bairrosCriados[simulador->quantidadeBairros];

    for (int i = 0; i < simulador->quantidadeBairros; i++)
    {
        Bairro novoBairro = gerarBairro();

        cadastrarBairro(&(simulador->bairros), novoBairro);

        bairrosCriados[i] = resgatarCadastroBairro(&(simulador->bairros), novoBairro.id);
    }

    /*
        Cria unidades de serviço aleatórias
        e as associa aos primeiros bairros.
    */
    for (int i = 0; i < simulador->quantidadeBombeiros; i++)
    {
        Bombeiro novoBombeiro = gerarBombeiro();

        cadastrarBombeiro(&(simulador->bombeiros), novoBombeiro);

        // Associamos a unidade de serviço ao bairro.
        if (i < simulador->quantidadeBairros)
        {
            inserirValorListaCruzada(&(simulador->bairroUnidade),
                                     TUS_BOMBEIRO,
                                     bairrosCriados[i]->id,
                                     novoBombeiro.id);
        }
    }

    for (int i = 0; i < simulador->quantidadeHospitais; i++)
    {
        Hospital novoHospital = gerarHospital();

        cadastrarHospital(&(simulador->hospitais), novoHospital);

        // Associamos a unidade de serviço ao bairro.
        if (i < simulador->quantidadeBairros)
        {
            inserirValorListaCruzada(&(simulador->bairroUnidade),
                                     TUS_HOSPITAL,
                                     bairrosCriados[i]->id,
                                     novoHospital.id);
        }
    }

    for (int i = 0; i < simulador->quantidadePolicias; i++)
    {
        Policia novaPolicia = gerarPolicia();

        cadastrarPolicia(&(simulador->policias), novaPolicia);

        // Associamos a unidade de serviço ao bairro.
        if (i < simulador->quantidadeBairros)
        {
            inserirValorListaCruzada(&(simulador->bairroUnidade),
                                     TUS_POLICIA,
                                     bairrosCriados[i]->id,
                                     novaPolicia.id);
        }
    }

    return true;
}

bool rodarSimulacao(Simulador * simulador)
{
    calcularTempoAtual(simulador->inicioSimulacao);

    /*
        Inicializa uma seed para os eventos aleatórios.
    */
    srand(time(NULL));

    bool entidadesCriadas = criarEntidades(simulador);

    if (!entidadesCriadas) return false;

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

                Profissional * profissionalTabela = resgatarProfissionalAleatorio(&(simulador->profissionais), simulador->quantidadeProfissionais);

                inserirValorPilha(&(profissionalTabela->historicoAtendimento), novaOcorrencia);

                simulador->ocorrenciasPorID = inserirValorABB(simulador->ocorrenciasPorID, novaOcorrencia);

                simulador->ocorrenciasPorGravidade = inserirValorAVL(simulador->ocorrenciasPorGravidade, novaOcorrencia);

                printf("\n[%s]: Nova ocorrência: \n", simulador->tempoAtualSimulacao);

                exibirOcorrencia(novaOcorrencia);

                printf("\n  -Profissional que atendeu a ocorrencia:\n");

                exibirProfissional(*profissionalTabela);

                inserirFilaGravidade(&(simulador->filaAtendimento), novaOcorrencia);
            }
        }


        if(!estaVaziaFilaP(&(simulador->filaAtendimento)))
        {
            Ocorrencia ocorrencia = removerOcorrenciaFila(&(simulador->filaAtendimento));

            printf("\n[%s]: Ocorrência retirada da fila de atendimento: %s\n",
                   simulador->tempoAtualSimulacao, ocorrencia.id);

            Bairro * bairroProximo = procurarBairroProximo(&(simulador->bairroUnidade),
                                                           &(simulador->bairros),
                                                           ocorrencia);

            printf("\n[%s]: Ocorrência \"%s\" enviada ao bairro mais próximo: \n",
                   simulador->tempoAtualSimulacao,
                   ocorrencia.id);

            exibirBairro(*bairroProximo);

            switch(ocorrencia.tipo)
            {
                case OCORRENCIA_BOMBEIRO:

                    inserirFilaGravidade(&(simulador->filaBombeiro), ocorrencia);

                    printf("\n[%s]: Ocorrência adicionada à fila de atendimento de bombeiro: %s\n",
                           simulador->tempoAtualSimulacao,
                           ocorrencia.id);
                    break;

                case OCORRENCIA_HOSPITAL:

                    inserirFilaGravidade(&(simulador->filaHospital), ocorrencia);

                    printf("\n[%s]: Ocorrência adicionada à fila de atendimento de hospital: %s\n",
                           simulador->tempoAtualSimulacao,
                           ocorrencia.id);

                    break;

                case OCORRENCIA_POLICIA:

                    inserirFilaGravidade(&(simulador->filaPolicia), ocorrencia);

                    printf("\n[%s]: Ocorrência adicionada à fila de atendimento de polícia: %s\n",
                           simulador->tempoAtualSimulacao,
                           ocorrencia.id);

                    break;

            }
        }

        tratarFilaOcorrencia(&(simulador->filaBombeiro),
                             simulador->tempoAtualSimulacao,
                             "bombeiro");

        tratarFilaOcorrencia(&(simulador->filaHospital),
                             simulador->tempoAtualSimulacao,
                             "hospital");

        tratarFilaOcorrencia(&(simulador->filaPolicia),
                             simulador->tempoAtualSimulacao,
                             "polícia");

        simulador->tempoSimulacao++;

        sleep(1); // Espera 1 segundo.
    }

    return true;
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
            if (novaQuantidade > MAX_BAIRROS) return false;

            simulador->quantidadeBairros = novaQuantidade;
            return true;

        case ENTIDADE_CIDADAO:
            simulador->quantidadeCidadaos = novaQuantidade;
            return true;

        case ENTIDADE_BOMBEIRO:
            if (novaQuantidade > MAX_BAIRROS) return false;

            simulador->quantidadeBombeiros = novaQuantidade;
            return true;

        case ENTIDADE_HOSPITAL:
            if (novaQuantidade > MAX_BAIRROS) return false;

            simulador->quantidadeHospitais = novaQuantidade;
            return true;

        case ENTIDADE_POLICIA:
            if (novaQuantidade > MAX_BAIRROS) return false;

            simulador->quantidadePolicias = novaQuantidade;
            return true;

        case ENTIDADE_SAMU:
            if (novaQuantidade > MAX_BAIRROS) return false;

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
    limparTabela(&(simulador->profissionais));
    limparTabela(&(simulador->bombeiros));
    limparTabela(&(simulador->hospitais));
    limparTabela(&(simulador->policias));

    destruirListaCruzada(&(simulador->bairroUnidade));

    limparFilaPrioridade(&(simulador->filaAtendimento));
    limparFilaPrioridade(&(simulador->filaBombeiro));
    limparFilaPrioridade(&(simulador->filaHospital));
    limparFilaPrioridade(&(simulador->filaPolicia));
    limparFilaPrioridade(&(simulador->filaSamu));

    destruirABB(simulador->ocorrenciasPorID);
    destruirAVL(simulador->ocorrenciasPorGravidade);

    return true;
}
