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

                printf("\n** Simulação Iniciada **\n");

                sleep(1); // Apenas uma decoração.

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

                if(limparSimulacao(&simulador))
                {
                    simulador = criarSimulador();

                    printf("\n** Simulação reiniciada com sucesso. **\n");
                }
                else
                {
                    printf("\n** Não foi possível reiniciar a simulação. **\n");
                }
                break;


            case 4:
            {

                char id[MAX_ID];

                printf("\nDigite o ID da ocorrência que deve ser procurada: ");

                fflush(stdin);

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

            case 5:

                if (simulador.ocorrenciasPorID)
                {
                    printf("\n** Listando todas as ocorrências. **\n");

                    relatorioOcorrencias(simulador.ocorrenciasPorID);
                }
                else
                {
                    printf("\n** Não há nenhuma ocorrência registrada. **\n");
                }
                break;

            case 6:

                if (simulador.ocorrenciasPorID)
                {
                    printf("1 - Bombeiro\n");
                    printf("2 - Hospital\n");
                    printf("3 - Polícia\n");


                    int tipoEscolhido = 0;

                    do
                    {
                        printf("Digite o tipo das ocorrências: ");
                        scanf("%d", &tipoEscolhido);
                    } while (tipoEscolhido < 1 || tipoEscolhido > 3);

                    relatorioOcorrenciasTipo(simulador.ocorrenciasPorID, tipoEscolhido - 1);
                }
                else
                {
                    printf("\n** Não há nenhuma ocorrência registrada. **\n");
                }

                break;

            case 7:

                if(simulador.ocorrenciasPorGravidade)
                {
                    printf("\n** Listando as ocorrências pela gravidade (da menor para a maior). **\n");
                    listarOcorrenciasPorGravidade(simulador.ocorrenciasPorGravidade);
                }
                else
                {
                    printf("\n** Não há nenhuma ocorrência registrada. **\n");
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
                    printf("\n** Histórico de atendimentos do profissional %s: **\n", profissionalEncontrado->cidadao.nome);
                    exibirHistoricoAtendimento(*profissionalEncontrado);
                }
                else
                {
                    printf("\n** Profissional não encontrado. ** \n");
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

                printf("\n** Opção inválida. ** \n");
                break;

        }

        printf("\nPressione ENTER para continuar...");

        fflush(stdin); // Limpa o buffer, caso algo tenha sobrado.
        getchar(); // Espera o ENTER.

    }while(opcao != 0);
}
