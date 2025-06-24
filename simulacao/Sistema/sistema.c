#include "utilidades_sistema/utilidades_sistema.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>


void executarSistema()
{
    setlocale(LC_ALL, "Portuguese");

    mensagemBoasVindas();

    Simulador simulador = criarSimulador();

    int opcao = 0;

    do{

        opcao = rodarMenu();

        switch(opcao)
        {
            case 1:

                printf("\n** Simulação Iniciada **\n");

                if (rodarSimulacao(&simulador))
                {
                    printf("\n** Simulação finalizada com sucesso. **\n");
                }
                else
                {
                    printf("\n** Houve algum problema ao finalizar o simulador. ** \n");
                }

                break;

            case 2:

                if(configurarSimulacao(&simulador))
                {
                    printf("\n** Configurações feitas com sucesso. **\n");
                }
                else
                {
                    printf("\n** Houve algum problema ao configurar o simulador. ** \n");
                }

                break;

            case 3:
            {

                char id[MAX_ID];

                printf("\nDigite o ID da ocorrência que deve ser procurada: ");

                fgets(id, MAX_ID, stdin);

                id[strcspn(id, "\n")] = 0;

                Ocorrencia *ocorrenciaEncontrada = buscarOcorrenciaPorID(simulador.ocorrenciasPorID, id);

                if(ocorrenciaEncontrada != NULL)
                {
                    printf("\n** Ocorrência encontrada. **\n");
                    exibirOcorrencia(*ocorrenciaEncontrada);
                }
                else
                {
                    printf("\n** Ocorrência não encontrada. ** \n");
                }

                break;
            }

            case 4:

                printf("\n** Listando todas as ocorrências. **\n");
                relatorioOcorrencias(simulador.ocorrenciasPorID);
                break;

            case 5:

                printf("\n** Listando as ocorrências pela gravidade(da menor para a maior). **\n");
                //listarOcorrenciasPorGravidade(simulador.ocorrenciasPorGravidade);
                break;

            case 6:
            {
                char idCidadao[MAX_ID];
                printf("\nDigite o ID do cidadão que deve ser procurado: ");
                fgets(idCidadao, MAX_ID, stdin);
                idCidadao[strcspn(idCidadao, "\n")] = 0;

                // TO-DO: Arrumar falta do cidadaosPorID
                /*Cidadao *cidadaoEncontrado = buscarCidadaoPorID(&(simulador.cidadaosPorID), idCidadao);

                if (cidadaoEncontrado != NULL)
                {
                    printf("\n** Cidadão encontrado! **\n");
                    exibirCidadao(*cidadaoEncontrado);
                }
                else
                {
                    printf("\n** Cidadão não encontrado. ** \n");
                }*/
                break;
            }

            case 7:
            {

                char idProfissional[MAX_ID];
                printf("\nDigite o ID do profissional: ");
                fgets(idProfissional, MAX_ID, stdin);
                idProfissional[strcspn(idProfissional, "\n")] = 0;

                // TO-DO: Arrumar falta do profissionaisPorID
                /*
                Profissional *profissionalEncontrado = buscarProfissionalPorID(&(simulador.profissionaisPorID),
                                                                               idProfissional);

                if (profissionalEncontrado != NULL)
                {
                    printf("\n** Histórico de atendimentos do profissional %s: **\n", profissionalEncontrado->cidadao.nome);
                    exibirHistoricoAtendimento(*profissionalEncontrado);
                }
                else
                {
                    printf("\n** Profissional não encontrado. ** \n");
                }
                */
                break;
            }

            case 8:
                exibirTodosAtendimentos(&simulador.profissionais, simulador.quantidadeProfissionais);
                break;

            case 0:
                limparSimulacao(&simulador);

                printf("\n** Saindo. ** \n");

                return;

            default:

                printf("\n** Opção inválida. ** \n");
                break;

        }

        printf("\nPressione ENTER para continuar...");

        while (getchar() != '\n'); // Limpa o buffer, caso algo tenha sobrado.
        getchar(); // Espera o ENTER.

    }while(opcao != 0);
}
