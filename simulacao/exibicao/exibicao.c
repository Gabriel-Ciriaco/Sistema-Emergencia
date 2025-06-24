#include "exibicao.h"

#include "../../estruturas/tipos_abstratos/pilha/pilha.h"


void exibirCidadao(Cidadao cidadao)
{
    printf("\n\tDados da Pessoa\n");
    printf("\n\t  -ID: %s\n", cidadao.id);
    printf("\n\t  -Nome: %s\n", cidadao.nome);
    printf("\n\t  -CPF: %s\n", cidadao.cpf);
    printf("\n\t  -Telefone de Emergência: %s\n", cidadao.telefoneEmergencia);
}

void exibirProfissional(Profissional profissional)
{
    printf("\n\tDados do Profissional:\n");

    exibirCidadao(profissional.cidadao);
}

void exibirOcorrencia(Ocorrencia ocorrencia)
{
    printf("\n\tDados da Ocorrência\n");

    printf("\n\t  -ID: %s\n", ocorrencia.id);

    printf("\n\t  -Gravidade: ");

    switch(ocorrencia.gravidade)
    {
        case GRAVIDADE_BAIXA:
            printf("Baixa\n");
            break;

        case GRAVIDADE_MEDIA:
            printf("Média\n");
            break;

        case GRAVIDADE_ALTA:
            printf("Alta\n");
            break;
    }

    printf("\n\t  -Hora da Ocorrência: %s\n", ocorrencia.horaOcorrencia);

    printf("\n\t  -Descrição: %s\n", ocorrencia.descricao);

    if (ocorrencia.vitima)
    {
        printf("\n\t  -Vítima: %s\n", ocorrencia.vitima->id);
    }

    if (ocorrencia.responsavel)
    {
        printf("\n\t  -Responsável: %s\n", ocorrencia.responsavel->id);
    }
}

void exibirHistoricoAtendimento(Profissional profissional)
{
    exibirProfissional(profissional);

    if (estaVaziaPilha(&profissional.historicoAtendimento))
    {
        printf("\n\t -Nenhuma ocorrência atendida pelo profissional.\n");

        return;
    }

    while(!estaVaziaPilha(&profissional.historicoAtendimento))
    {
        Ocorrencia ocorrencia = removerValorPilha(&(profissional.historicoAtendimento));

        printf("\n\t  -Ocorrência atendida pelo profissional:\n");

        exibirOcorrencia(ocorrencia);
    }

}

void exibirTodosAtendimentos(TabelaHash * profissionais, int quantidadeProfissionais)
{
    int i = 0;

    int profissionaisMostrados = 0;

    printf("\n\n** Histórico de Atendimento dos Profissionais **\n");

    while(i < MAX_TABELA_HASH &&
          profissionaisMostrados < quantidadeProfissionais)
    {
        NoHash * no = profissionais->tabela[i];

        if (no)
        {
            do
            {
                printf("\n");

                exibirHistoricoAtendimento(no->valor.profissional);

                printf("\n");

                profissionaisMostrados++;

                no = no->prox;

            } while(no);
        }

        i++;
    }
}
