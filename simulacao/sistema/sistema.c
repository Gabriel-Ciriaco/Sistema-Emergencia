#include "utilidades_sistema/utilidades_sistema.h"
#include "../exibicao/exibicao.h"
#include "../cadastramento/cadastro.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
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

                sleep(1); // Apenas uma decora��o.

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

                if(limparSimulacao(&simulador))
                {
                    simulador = criarSimulador();

                    printf("\n** Simula��o reiniciada com sucesso. **\n");
                }
                else
                {
                    printf("\n** N�o foi poss�vel reiniciar a simula��o. **\n");
                }
                break;


            case 4:
            {

                char id[MAX_ID];

                printf("\nDigite o ID da ocorr�ncia que deve ser procurada: ");

                fflush(stdin);

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

            case 5:

                if (simulador.ocorrenciasPorID)
                {
                    printf("\n** Listando todas as ocorr�ncias. **\n");

                    relatorioOcorrencias(simulador.ocorrenciasPorID);
                }
                else
                {
                    printf("\n** N�o h� nenhuma ocorr�ncia registrada. **\n");
                }
                break;

            case 6:

                if (simulador.ocorrenciasPorID)
                {
                    printf("1 - Bombeiro\n");
                    printf("2 - Hospital\n");
                    printf("3 - Pol�cia\n");


                    int tipoEscolhido = 0;

                    do
                    {
                        printf("Digite o tipo das ocorr�ncias: ");
                        scanf("%d", &tipoEscolhido);
                    } while (tipoEscolhido < 1 || tipoEscolhido > 3);

                    relatorioOcorrenciasTipo(simulador.ocorrenciasPorID, tipoEscolhido - 1);
                }
                else
                {
                    printf("\n** N�o h� nenhuma ocorr�ncia registrada. **\n");
                }

                break;

            case 7:

                if(simulador.ocorrenciasPorGravidade)
                {
                    printf("\n** Listando as ocorr�ncias pela gravidade (da menor para a maior). **\n");
                    listarOcorrenciasPorGravidade(simulador.ocorrenciasPorGravidade);
                }
                else
                {
                    printf("\n** N�o h� nenhuma ocorr�ncia registrada. **\n");
                }

                break;


            case 8:
            {

                char idProfissional[MAX_ID];
                printf("\nDigite o ID do profissional: ");

                fflush(stdin);

                fgets(idProfissional, MAX_ID, stdin);
                idProfissional[strcspn(idProfissional, "\n")] = 0;


                Profissional *profissionalEncontrado = resgatarCadastroProfissional(&(simulador.profissionais), idProfissional);

                if (profissionalEncontrado != NULL)
                {
                    printf("\n** Hist�rico de atendimentos do profissional %s: **\n", profissionalEncontrado->cidadao.nome);
                    exibirHistoricoAtendimento(*profissionalEncontrado);
                }
                else
                {
                    printf("\n** Profissional n�o encontrado. ** \n");
                }

                break;
            }

            case 9:
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

        fflush(stdin); // Limpa o buffer, caso algo tenha sobrado.
        getchar(); // Espera o ENTER.

    }while(opcao != 0);
}
