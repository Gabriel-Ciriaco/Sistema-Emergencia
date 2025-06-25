#include "exibicao.h"

#include "../../estruturas/tipos_abstratos/pilha/pilha.h"

#include <stdio.h>

void exibirPosicao(Posicao pos)
{
    printf("\n\t  -Posição: ");

    char hemisferio_latitude = (pos.y >= 0) ? 'N' : 'S';
    char hemisferio_longitude = (pos.x >= 0) ? 'E' : 'W';

    printf("%.6fº%c %.6fº%c\n",
           (pos.y >= 0 ? pos.y : -pos.y),
           hemisferio_latitude,
           (pos.x >=0 ? pos.x : -pos.x),
           hemisferio_longitude);
}

void exibirCidadao(Cidadao cidadao)
{
    printf("---------------------------");
    printf("\n\tDados da Pessoa\n");
    printf("\n\t  -ID: %s\n", cidadao.id);
    printf("\n\t  -Nome: %s\n", cidadao.nome);
    printf("\n\t  -CPF: %s\n", cidadao.cpf);
    printf("\n\t  -Telefone de Emergência: %s\n", cidadao.telefoneEmergencia);
    exibirPosicao(cidadao.pos);
}

void exibirProfissional(Profissional profissional)
{
    printf("---------------------------");
    printf("\n\tDados do Profissional:\n");

    exibirCidadao(profissional.cidadao);
}

void exibirOcorrencia(Ocorrencia ocorrencia)
{
    printf("---------------------------");
    printf("\n\tDados da Ocorrência\n");

    printf("\n\t  -ID: %s\n", ocorrencia.id);

    printf("\n\t  -Tipo da Ocorrência: ");

    switch(ocorrencia.tipo)
    {
        case OCORRENCIA_BOMBEIRO:
            printf("Ocorrência do Corpo de Bombeiro\n");
            break;

        case OCORRENCIA_HOSPITAL:
            printf("Ocorrência hospitalar\n");
            break;

        case OCORRENCIA_POLICIA:
            printf("Ocorrência policial\n");
            break;
    }

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

    if (profissionaisMostrados == 0)
    {
        printf("\n** Não há profissionais cadastrados. **\n");
    }
}
