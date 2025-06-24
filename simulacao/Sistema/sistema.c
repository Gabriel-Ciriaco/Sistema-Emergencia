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
            {

                char id[MAX_ID];

                printf("\nDigite o ID da ocorr�ncia que deve ser procurada: ");

                fgets(id, MAX_ID, stdin);

                id[strcspn(id, "\n")] = 0;

                Ocorrencia *ocorrenciaEncontrada = buscarOcorrenciaPorID(simulador.ocorrenciasPorID, id);

                if(ocorrenciaEncontrada != NULL)
                {
                    printf("\n** Ocorr�ncia encontrada. **\n");
                    exibirOcorrencia(*ocorrenciaEncontrada);
                }
                else
                {
                    printf("\n** Ocorr�ncia n�o encontrada. ** \n");
                }

                break;
            }

            case 4:

                printf("\n** Listando todas as ocorr�ncias. **\n");
                relatorioOcorrencias(simulador.ocorrenciasPorID);
                break;

            case 5:

                printf("\n** Listando as ocorr�ncias pela gravidade(da menor para a maior). **\n");
                //listarOcorrenciasPorGravidade(simulador.ocorrenciasPorGravidade);
                break;

            case 6:
            {
                char idCidadao[MAX_ID];
                printf("\nDigite o ID do cidad�o que deve ser procurado: ");
                fgets(idCidadao, MAX_ID, stdin);
                idCidadao[strcspn(idCidadao, "\n")] = 0;

                // TO-DO: Arrumar falta do cidadaosPorID
                /*Cidadao *cidadaoEncontrado = buscarCidadaoPorID(&(simulador.cidadaosPorID), idCidadao);

                if (cidadaoEncontrado != NULL)
                {
                    printf("\n** Cidad�o encontrado! **\n");
                    exibirCidadao(*cidadaoEncontrado);
                }
                else
                {
                    printf("\n** Cidad�o n�o encontrado. ** \n");
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
                    printf("\n** Hist�rico de atendimentos do profissional %s: **\n", profissionalEncontrado->cidadao.nome);
                    exibirHistoricoAtendimento(*profissionalEncontrado);
                }
                else
                {
                    printf("\n** Profissional n�o encontrado. ** \n");
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

                printf("\n** Op��o inv�lida. ** \n");
                break;

        }

        printf("\nPressione ENTER para continuar...");

        while (getchar() != '\n'); // Limpa o buffer, caso algo tenha sobrado.
        getchar(); // Espera o ENTER.

    }while(opcao != 0);
}
