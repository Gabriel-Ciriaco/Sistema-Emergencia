#include "simulacao.h"
#include "./geradores/geradores.h"

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
    srand(time(NULL));

    printf("\n[%s]: ** Simulação iniciada **\n", simulador->inicioSimulacao);

    while (simulador->tempoSimulacao < simulador->tempoSimulacaoMaximo)
    {
        time_t t = time(NULL);

        struct tm horaAtual = *localtime(&t);


        strftime(simulador->tempoAtualSimulacao, FORMATO_TEMPO, "%H:%M:%S", &horaAtual);

        /*
            TO-DO: Adicionar a simulação em si.
        */

       Cidadao teste = gerarCidadao();

       if (strcasecmp(teste.nome, "") == 0)
       {
           printf("\n** Não foi possível gerar um cidadão! **\n");
       }
       else
       {
           printf("\n[%s]\n** Cidadao aleatório **", simulador->tempoAtualSimulacao);

           printf("\n-ID: %s\n-Nome: %s\n-Idade: %d\n-CPF: %s\n-TELEFONE: %s\n",
                  teste.id, teste.nome, teste.idade, teste.cpf, teste.telefoneEmergencia);
       }

       /*
        TO-DO: Apagar tudo que está aqui.

        Este é um teste para a geração aleatória de ocorrências.
       */
       Ocorrencia ocorrenciaTeste = gerarOcorrencia(horaAtual, NULL, NULL);

       printf("\n** Nova Ocorrência **");

       switch(ocorrenciaTeste.tipo)
       {
           case OCORRENCIA_BOMBEIRO:
               printf("\n-Tipo de Ocorrência: Bombeiro");
           break;

           case OCORRENCIA_HOSPITAL:
               printf("\n-Tipo de Ocorrência: Hospital");
           break;

           case OCORRENCIA_POLICIA:
               printf("\n-Tipo de Ocorrência: Polícia");
           break;
       }

       switch(ocorrenciaTeste.gravidade)
       {
           case GRAVIDADE_BAIXA:
               printf("\n-Gravidade da Ocorrência: Baixa");
           break;

           case GRAVIDADE_MEDIA:
               printf("\n-Gravidade da Ocorrência: Média");
           break;

           case GRAVIDADE_ALTA:
               printf("\n-Gravidade da Ocorrência: Alta");
           break;
       }

       printf("\n-Descrição da Ocorrência: %s\n\n", ocorrenciaTeste.descricao);

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
