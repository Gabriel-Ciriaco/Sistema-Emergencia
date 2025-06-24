#include "utilidades_sistema.h"

#include "../../../estruturas/cidadao/cidadao.h"
#include "../../../estruturas/bairro/bairro.h"
#include "../../../estruturas/vetoriais/posicao.h"

void mensagemBoasVindas()
{
    printf("\n***Bem-vindo a RonalVilla!***\n");
    printf("\nEste � um simulador de atendimento de emerg�ncia urbana,
           "onde voc� poder� observar:\n");
    printf("- A gera��o din�mica de ocorr�ncias.\n");
    printf("- O despacho e prioriza��o de equipes de servi�o
           "(Bombeiros, SAMU, Pol�cia, Hospital).\n");
    printf("- Mas, acima de tudo, o impacto das estruturas de
           "dados na efici�ncia do sistema.\n");
}

bool configurarSimulacao(Simulador *simulador)
{
    int novoTempoMaxSimulacao, novaQtdOcorrencias,
    novaQtdBairros, novaQtdCidadaos, novaQtdBomb,
    novaQtdHosp, novaQtdPol, novaQtdSamu;

    printf("\nDigite o novo tempo m�ximo de simula��o: ");
    scanf("%d", &novoTempoMaxSimulacao);
    printf("\nDigite a nova quantidade m�xima de ocorr�ncias por ciclo: ");
    scanf("%d", &novaQtdOcorrencias);
    printf("\nDigite a nova quantidade de bairros: ");
    scanf("%d", &novaQtdBairros);
    printf("\nDigite a nova quantidade de cidad�os: ");
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

Ocorrencia *buscarOcorrenciaPorID(Arvore *raiz, char const *idOcorrencia)
{
    Ocorrencia *ocorrenciaEncontrada = buscarValorABB(raiz, idOcorrencia);

    return ocorrenciaEncontrada;
}

void exibirOcorrencia(Ocorrencia *ocorrencia)
{
    printf("\nOcorr�ncia: %s\n-Descri��o: %s\n-V�tima: %s\n",
                        ocorrencia->id,
                        ocorrencia->descricao,
                        ocorrencia->vitima->nome);

                if (ocorrencia->responsavel)
                {
                    printf("-Respons�vel: %s\n", ocorrencia->responsavel->nome);
                }

                switch(ocorrencia->gravidade)
                {
                    case GRAVIDADE_BAIXA:
                        printf("-Gravidade: Baixa\n");

                        break;

                    case GRAVIDADE_MEDIA:
                        printf("-Gravidade: M�dia\n");

                        break;

                    case GRAVIDADE_ALTA:
                        printf("-Gravidade: Alta\n");

                        break;
                }
}

void relatorioOcorrencias(Arvore *raiz)
{
    if(raiz != NULL)
    {
        relatorioOcorrencias(raiz->esq);
        exbirOcorrencia(&(raiz->ocorrencia));
        relatorioOcorrencias(raiz->dir);
    }
}

void listarOcorrenciasPorGravidade(No *raiz)
{
    if (raiz != NULL)
    {
        listarOcorrenciasPorGravidade(raiz->esq);
        exibirOcorrencia(&(raiz->ocorrencia));
        listarOcorrenciasPorGravidade(raiz->dir);
    }
}

void exibirCidadao(Cidadao *cidadao)
{
    printf("ID: %s\n", cidadao->id);
    printf("Nome: %s\n", cidadao->nome);
    printf("Idade: %d\n", cidadao->idade);
    printf("CPF: %s\n", cidadao->cpf);
    printf("Telefone de Emerg�ncia: %s\n", cidadao->telefoneEmergencia);
    printf("Bairro: %s\n", cidadao->bairro->nome);
    printf("Posi��o (X, Y): (%d, %d)\n", cidadao->pos.x, cidadao->pos.y);
}

void exibirHistoricoAtendimentos(Pilha *pilha)
{
    if(estaVaziaPilha(pilha))
    {
        printf("Hist�rico de atendimentos vazio!\n");
        return;
    }

    while(pilha->topo != -1)
    {
         Ocorrencia ocorrencia = pilha->pilha[pilha->topo--];

         printf("\nOcorr�ncia: %s\n-Descri��o: %s\n-V�tima: %s\n",
                        ocorrencia.id,
                        ocorrencia.descricao,
                        ocorrencia.vitima->nome);

                if (ocorrencia.responsavel)
                {
                    printf("-Respons�vel: %s\n", ocorrencia.responsavel->nome);
                }

                switch(ocorrencia.gravidade)
                {
                    case GRAVIDADE_BAIXA:
                        printf("-Gravidade: Baixa\n");

                        break;

                    case GRAVIDADE_MEDIA:
                        printf("-Gravidade: M�dia\n");

                        break;

                    case GRAVIDADE_ALTA:
                        printf("-Gravidade: Alta\n");

                        break;
                }
    }
}

int rodarMenu()
{
    int opcao;

    printf("\n*** MENU PRINCIPAL ***\n");
    printf("1 - Rodar simula��o\n");
    printf("2 - Configurar simula��o\n");
    printf("---------------------------\n");
    printf("3 - Buscar ocorr�ncia por ID\n");
    printf("4 - Listar todas as ocorr�ncias\n");
    printf("5 - Listar todas as ocorr�ncias por gravidade\n");
    printf("---------------------------\n");
    printf("6 - Buscar cidad�o por ID\n");
    printf("---------------------------\n");
    printf("7 - Visualizar hist�rico de atendimentos de um profissional\n");
    printf("---------------------------\n");
    printf("0 - Sair\n");
    printf("---------------------------\n");
    printf("Digite o n�mero da op��o escolhida:");
    scanf("%d", &opcao);

    return opcao;
}
