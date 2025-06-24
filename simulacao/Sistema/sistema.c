#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <locale.h>

#include "../simulacao.h"
#include "../../constantes-sistema/constantes-sistema.h"
#include "../../estruturas/tipos_abstratos/arvore_ABB/arvore_abb.h"
#include "../../estruturas/ocorrencia/ocorrencia.h"
#include "Utilidades_Sistema/utilidades_sistema.h"
#include "../../estruturas/tipos_abstratos/tabela_hash/tabela_hash.h"


void executarSistema()
{
    setlocale(LC_ALL, "Portuguese");

    mensagemBoasVindas();

    Simulador simulador = criarSimulador();

    int opcao;

    do{

        opcao = rodarMenu();

        switch(opcao)
        {
            case 1:

                printf("\n** Simula��o Iniciada **\n");

                if (rodarSimulacao(&simulador))
                {
                    printf("\n** Simula��o finalizada com sucesso. **\n");
                }
                else
                {
                    printf("\n** Houve algum problema ao finalizar o simulador. ** \n");
                }

                break;

            case 2:

                if(configurarSimulacao(&simulador))
                {
                    printf("\n** Configura��es feitas com sucesso. **\n");
                }
                else
                {
                    printf("\n** Houve algum problema ao configurar o simulador. ** \n");
                }

                break;

            case 3:

                char id[MAX_ID];
                printf("\nDigite o ID da ocorr�ncia que deve ser procurada: ");
                fgets(id, MAX_ID, stdin);
                id[strcspn(id, "\n")] = 0;

                Ocorrencia *ocorrenciaEncontrada = buscarOcorrenciaPorID(simulador->ocorrenciasPorID, id);

                if(ocorrenciaEncontrada != NULL)
                {
                    printf("\n** Ocorr�ncia encontrada. **\n");
                    exibirOcorrencia(ocorrenciaEncontrada);
                }
                else
                {
                    printf("\n** Ocorr�ncia n�o encontrada. ** \n");
                }

                break;

            case 4:

                printf("\n** Listando todas as ocorr�ncias. **\n");
                relatorioOcorrencias(simulador->ocorrenciasPorID);
                break;

            case 5:

                printf("\n** Listando as ocorr�ncias pela gravidade(da menor para a maior). **\n");
                listarOcorrenciasPorGravidade(simulador->ocorrenciasPorGravidade);
                break;

            case 6:

                char idCidadao[MAX_ID];
                printf("\nDigite o ID do cidad�o que deve ser procurado: ");
                fgets(idCidadao, MAX_ID, stdin);
                idCidadao[strcspn(idCidadao, "\n")] = 0;

                Cidadao *cidadaoEncontrado = buscarCidadaoPorID(&(simulador.cidadaosPorID), idCidadao);

                if (cidadaoEncontrado != NULL)
                {
                    printf("\n** Cidad�o encontrado! **\n");
                    exibirCidadao(cidadaoEncontrado);
                }
                else
                {
                    printf("\n** Cidad�o n�o encontrado. ** \n");
                }
                break;

            case 7:

                char idProfissional[MAX_ID];
                printf("\nDigite o ID do profissional: ");
                fgets(idProfissional, MAX_ID, stdin);
                idProfissional[strcspn(idProfissional, "\n")] = 0;

                Profissional *profissionalEncontrado = buscarProfissionalPorID(&(simulador.profissionaisPorID),
                                                                               idProfissional);

                if (profissionalEncontrado != NULL)
                {
                    printf("\n** Hist�rico de atendimentos do profissional %s: **\n", profissionalEncontrado->cidadao.nome);
                    exibirHistoricoAtendimentos(&(profissionalEncontrado->historicoAtendimento));
                }
                else
                {
                    printf("\n** Profissional n�o encontrado. ** \n");
                }

                break;

            case 0:

                printf("\n** Saindo. ** \n", idProfissional);
                break;

            default:

                printf("\n** Op��o inv�lida. ** \n", idProfissional);
                break;

        }

    }while(opcao != 0);
}
