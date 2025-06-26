#include "utilidades_sistema.h"
#include "../../exibicao/exibicao.h"

#include "../../../estruturas/cidadao/cidadao.h"
#include "../../../estruturas/bairro/bairro.h"
#include "../../../estruturas/vetoriais/posicao.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void mensagemBoasVindas()
{
    printf("\n***Bem-vindo a RonalVilla!***\n");
    printf("\nEste é um simulador de atendimento de emergência urbana, onde você poderá observar:\n");
    printf("- A geração dinâmica de ocorrências.\n");
    printf("- O despacho e priorização de equipes de serviço (Bombeiros, SAMU, Polícia, Hospital).\n");
    printf("- Mas, acima de tudo, o impacto das estruturas de dados na eficiência do sistema.\n");
}

bool configurarSimulacao(Simulador *simulador)
{
    int novoTempoMaxSimulacao, novaQtdOcorrencias,
    novaQtdBairros, novaQtdCidadaos, novaQtdBomb,
    novaQtdHosp, novaQtdPol, novaQtdSamu;

    printf("\nDigite o novo tempo máximo de simulação: ");
    scanf("%d", &novoTempoMaxSimulacao);
    printf("\nDigite a nova quantidade máxima de ocorrências por ciclo: ");
    scanf("%d", &novaQtdOcorrencias);
    printf("\nDigite a nova quantidade de bairros: ");
    scanf("%d", &novaQtdBairros);
    printf("\nDigite a nova quantidade de cidadãos: ");
    scanf("%d", &novaQtdCidadaos);
    printf("\nDigite a nova quantidade de bombeiros: ");
    scanf("%d", &novaQtdBomb);
    printf("\nDigite a nova quantidade de hospitais: ");
    scanf("%d", &novaQtdHosp);
    printf("\nDigite a nova quantidade de policias: ");
    scanf("%d", &novaQtdPol);
    printf("\nDigite a nova quantidade de SAMUs: ");
    scanf("%d", &novaQtdSamu);

    return alterarTempoMaximoSimulacao(simulador, novoTempoMaxSimulacao) &&
            alterarQuantidadeOcorrenciasCiclo(simulador, novaQtdOcorrencias) &&
            alterarQuantidadeEntidade(simulador, ENTIDADE_BAIRRO, novaQtdBairros) &&
            alterarQuantidadeEntidade(simulador, ENTIDADE_CIDADAO, novaQtdCidadaos) &&
            alterarQuantidadeEntidade(simulador, ENTIDADE_BOMBEIRO, novaQtdBomb) &&
            alterarQuantidadeEntidade(simulador, ENTIDADE_HOSPITAL, novaQtdHosp) &&
            alterarQuantidadeEntidade(simulador, ENTIDADE_POLICIA, novaQtdPol) &&
            alterarQuantidadeEntidade(simulador, ENTIDADE_SAMU, novaQtdSamu);

}

Ocorrencia *buscarOcorrenciaPorID(ArvoreABB *raiz, char const *idOcorrencia)
{
    ArvoreABB * valor = buscarValorABB(raiz, idOcorrencia);

    if (!valor) return NULL;

    Ocorrencia *ocorrenciaEncontrada = &(valor->ocorrencia);

    return ocorrenciaEncontrada;
}

void relatorioOcorrencias(ArvoreABB *raiz)
{
    if(raiz != NULL)
    {
        relatorioOcorrencias(raiz->esq);
        exibirOcorrencia(raiz->ocorrencia);
        relatorioOcorrencias(raiz->dir);
    }
}

void relatorioOcorrenciasTipo(ArvoreABB *raiz, TipoOcorrencia tipoOcorrencia)
{
    if(raiz != NULL)
    {
        relatorioOcorrenciasTipo(raiz->esq, tipoOcorrencia);

        if (raiz->ocorrencia.tipo == tipoOcorrencia)
        {
            exibirOcorrencia(raiz->ocorrencia);
        }

        relatorioOcorrenciasTipo(raiz->dir, tipoOcorrencia);
    }
}

void listarOcorrenciasPorGravidade(NoAvl *raiz)
{
    if (raiz != NULL)
    {
        listarOcorrenciasPorGravidade(raiz->esq);
        exibirOcorrencia(raiz->ocorrencia);
        listarOcorrenciasPorGravidade(raiz->dir);
    }
}

int rodarMenu()
{
    int opcao;

    printf("\n\n*** MENU PRINCIPAL ***\n\n");
    printf("1 - Rodar simulação\n");
    printf("2 - Configurar simulação\n");
    printf("3 - Reiniciar simulação\n");
    printf("---------------------------\n");
    printf("4 - Buscar ocorrência por ID\n");
    printf("5 - Listar todas as ocorrências\n");
    printf("6 - Listar todas as ocorrências por tipo\n");
    printf("7 - Listar todas as ocorrências por gravidade\n");
    printf("---------------------------\n");
    printf("8 - Visualizar histórico de atendimentos de um profissional\n");
    printf("---------------------------\n");
    printf("9 - Visualizar todos os históricos de atendimentos\n");
    printf("---------------------------\n");
    printf("0 - Sair\n");
    printf("---------------------------\n");
    printf("Digite o número da opção escolhida: ");
    scanf("%d", &opcao);

    return opcao;
}
