#include "exibicao.h"

#include "../../estruturas/tipos_abstratos/pilha/pilha.h"

#include <stdio.h>
#include <math.h>


void floatParaCoordenadas(float coord, char positiva, char negativa)
{
    char direcao = (coord >= 0) ? positiva : negativa;

    coord = fabs(coord);

    int graus = (int) coord;

    float min_float = (coord - graus) * 60.0;
    int minutos = (int) min_float;

    int segundos = (int) ((min_float - (float) minutos) * 60.0);

    printf("%d�%02d'%02d\"%c", graus, minutos, segundos, direcao);
}

void exibirPosicao(Posicao pos)
{
    printf("\n\t  -Posi��o: ");

    floatParaCoordenadas(pos.y, 'N', 'S');
    printf(" ");
    floatParaCoordenadas(pos.x, 'E', 'W');
    printf("\n");
}

void exibirBairro(Bairro bairro)
{
    printf("---------------------------");
    printf("\n\tDados do Bairro\n");
    printf("\n\t  -ID: %s\n", bairro.id);
    printf("\n\t  -Nome: %s\n", bairro.nome);
    exibirPosicao(bairro.pos);
}

void exibirCidadao(Cidadao cidadao)
{
    printf("---------------------------");
    printf("\n\tDados da Pessoa\n");
    printf("\n\t  -ID: %s\n", cidadao.id);
    printf("\n\t  -Nome: %s\n", cidadao.nome);
    printf("\n\t  -CPF: %s\n", cidadao.cpf);
    printf("\n\t  -Telefone de Emerg�ncia: %s\n", cidadao.telefoneEmergencia);
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
    printf("\n\tDados da Ocorr�ncia\n");

    printf("\n\t  -ID: %s\n", ocorrencia.id);

    printf("\n\t  -Tipo da Ocorr�ncia: ");

    switch(ocorrencia.tipo)
    {
        case OCORRENCIA_BOMBEIRO:
            printf("Ocorr�ncia do Corpo de Bombeiro\n");
            break;

        case OCORRENCIA_HOSPITAL:
            printf("Ocorr�ncia hospitalar\n");
            break;

        case OCORRENCIA_POLICIA:
            printf("Ocorr�ncia policial\n");
            break;
    }

    printf("\n\t  -Gravidade: ");

    switch(ocorrencia.gravidade)
    {
        case GRAVIDADE_BAIXA:
            printf("Baixa\n");
            break;

        case GRAVIDADE_MEDIA:
            printf("M�dia\n");
            break;

        case GRAVIDADE_ALTA:
            printf("Alta\n");
            break;
    }

    printf("\n\t  -Hora da Ocorr�ncia: %s\n", ocorrencia.horaOcorrencia);

    printf("\n\t  -Descri��o: %s\n", ocorrencia.descricao);

    if (ocorrencia.vitima)
    {
        printf("\n\t  -V�tima: %s\n", ocorrencia.vitima->id);
    }

    if (ocorrencia.responsavel)
    {
        printf("\n\t  -Respons�vel: %s\n", ocorrencia.responsavel->id);
    }
}

void exibirHistoricoAtendimento(Profissional profissional)
{
    exibirProfissional(profissional);

    if (estaVaziaPilha(&profissional.historicoAtendimento))
    {
        printf("\n\t -Nenhuma ocorr�ncia atendida pelo profissional.\n");

        return;
    }

    while(!estaVaziaPilha(&profissional.historicoAtendimento))
    {
        Ocorrencia ocorrencia = removerValorPilha(&(profissional.historicoAtendimento));

        printf("\n\t  -Ocorr�ncia atendida pelo profissional:\n");

        exibirOcorrencia(ocorrencia);
    }

}

void exibirTodosAtendimentos(TabelaHash * profissionais, int quantidadeProfissionais)
{
    int i = 0;

    int profissionaisMostrados = 0;

    printf("\n\n** Hist�rico de Atendimento dos Profissionais **\n");

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
        printf("\n** N�o h� profissionais cadastrados. **\n");
    }
}
