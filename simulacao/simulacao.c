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

    /* Inicializa��o dos tempos da simula��o */

    novoSimulador.tempoSimulacao = 0;

    novoSimulador.tempoSimulacaoMaximo = MAX_TEMPO_SIMULACAO;


    /* Inicializa��o das quantidades */
    novoSimulador.quantidadeBairros = QTD_BAIRROS;

    novoSimulador.quantidadeCidadaos = QTD_CIDADAOS;

    novoSimulador.quantidadeBombeiros = QTD_BOMBEIROS;

    novoSimulador.quantidadeHospitais = QTD_HOSPITAIS;

    novoSimulador.quantidadePolicias = QTD_POLICIAS;

    novoSimulador.quantidadeSamus = QTD_SAMUS;

    /* Inicializa��o das tabelas */
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
        Inicializa uma seed para os eventos aleat�rios.
    */
    srand(time(NULL));

    printf("\n[%s]: ** Simula��o iniciada **\n", simulador->inicioSimulacao);

    while (simulador->tempoSimulacao < simulador->tempoSimulacaoMaximo)
    {
        time_t t = time(NULL);

        struct tm horaAtual = *localtime(&t);


        strftime(simulador->tempoAtualSimulacao, FORMATO_TEMPO, "%H:%M:%S", &horaAtual);

        /*
            TO-DO: Adicionar a simula��o em si.
        */

       Cidadao teste = gerarCidadao();

       if (strcasecmp(teste.nome, "") == 0)
       {
           printf("\n** N�o foi poss�vel gerar um cidad�o! **\n");
       }
       else
       {
           printf("\n[%s]\n** Cidadao aleat�rio **", simulador->tempoAtualSimulacao);

           printf("\n-ID: %s\n-Nome: %s\n-Idade: %d\n-CPF: %s\n-TELEFONE: %s\n",
                  teste.id, teste.nome, teste.idade, teste.cpf, teste.telefoneEmergencia);
       }

       /*
        TO-DO: Apagar tudo que est� aqui.

        Este � um teste para a gera��o aleat�ria de ocorr�ncias.
       */
       Ocorrencia ocorrenciaTeste = gerarOcorrencia(horaAtual, NULL, NULL);

       printf("\n** Nova Ocorr�ncia **");

       switch(ocorrenciaTeste.tipo)
       {
           case OCORRENCIA_BOMBEIRO:
               printf("\n-Tipo de Ocorr�ncia: Bombeiro");
           break;

           case OCORRENCIA_HOSPITAL:
               printf("\n-Tipo de Ocorr�ncia: Hospital");
           break;

           case OCORRENCIA_POLICIA:
               printf("\n-Tipo de Ocorr�ncia: Pol�cia");
           break;
       }

       switch(ocorrenciaTeste.gravidade)
       {
           case GRAVIDADE_BAIXA:
               printf("\n-Gravidade da Ocorr�ncia: Baixa");
           break;

           case GRAVIDADE_MEDIA:
               printf("\n-Gravidade da Ocorr�ncia: M�dia");
           break;

           case GRAVIDADE_ALTA:
               printf("\n-Gravidade da Ocorr�ncia: Alta");
           break;
       }

       printf("\n-Descri��o da Ocorr�ncia: %s\n\n", ocorrenciaTeste.descricao);

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
