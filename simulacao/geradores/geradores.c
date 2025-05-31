#include "geradores.h"
#include "../../constantes-sistema/constantes-sistema.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

Bairro gerarBairro(const char * nome, UnidadeServico unidadeServico)
{

    Bairro novoBairro;

    strcpy(novoBairro.nome, nome);

    sprintf(novoBairro.id, "BA%d", rand() % MAX_RAND_ID);

    novoBairro.pos.x = rand() % MAX_RAND_POS;

    novoBairro.pos.y = rand() % MAX_RAND_POS;

    return novoBairro;
}

int quantidadeNomesDisponiveis(char * NOMES_PATH)
{
    FILE * lista_nomes = fopen(NOMES_PATH, "r");

    if (!lista_nomes) return -1;


    int quantidadeNomes = 0;

    char linha[MAX_NOME];

    while(fgets(linha, sizeof(linha), lista_nomes))
    {
        // Procura e remove a quebra de linha.
        linha[strcspn(linha, "\r\n")] = '\0';

        int temLetra = false;

        // A linha tem que ter pelo menos uma letra.
        for (int j = 0; linha[j] != '\0'; j++)
        {
            if (isalpha(linha[j]))
            {
                temLetra = true;
                break;
            }
        }

        if (temLetra) quantidadeNomes++;
    }

    fclose(lista_nomes);

    return quantidadeNomes;
}

void nomeCidadaoAleatorio(char * nome)
{
    FILE * lista_nomes = fopen(NOMES_CIDADAO_PATH, "r");

    if (!lista_nomes)
    {
        perror("\n** Não foi possivel ler nomes_cidadao.txt **");

        strcpy(nome, ""); // Nome vazio, indicando erro.
    }
    else
    {
        int quantidadeNomes = quantidadeNomesDisponiveis(NOMES_CIDADAO_PATH);

        char nomes_possiveis[quantidadeNomes][MAX_NOME];

        char linha[MAX_NOME];

        int i = 0;

        while(fgets(linha, sizeof(linha), lista_nomes))
        {
            // Procura e remove a quebra de linha.
            linha[strcspn(linha, "\r\n")] = '\0';

            int temLetra = false;

            // A linha tem que ter pelo menos uma letra.
            for (int j = 0; linha[j] != '\0'; j++)
            {
                if (isalpha(linha[j]))
                {
                    temLetra = true;
                    break;
                }
            }

            if (temLetra)
            {
                strncpy(nomes_possiveis[i], linha, MAX_NOME);

                nomes_possiveis[i][MAX_NOME - 1] = '\0'; // Garantir a finalização da string.

                i++;
            }


        }

        strcpy(nome, nomes_possiveis[rand() % quantidadeNomes]);
    }

    fclose(lista_nomes);

}

Cidadao gerarCidadao()
{
    Cidadao novoCidadao;

    nomeCidadaoAleatorio(&novoCidadao.nome);

    return novoCidadao;

}


Bombeiro gerarBombeiro()
{
    Bombeiro novoBombeiro;

    sprintf(novoBombeiro.id, "BO%d", rand() % MAX_RAND_ID);

    if(rand() % 2 == 1)
    {
        novoBombeiro.emAtendimento = true;

    }else{

        novoBombeiro.emAtendimento = false;
    }

    novoBombeiro.pos.x = rand() % MAX_RAND_POS;

    novoBombeiro.pos.y = rand() % MAX_RAND_POS;

    return novoBombeiro;
}


Hospital gerarHospital(const char * nome)
{
    Hospital novoHospital;

    strcmp(novoHospital.nome, nome);

    sprintf(novoHospital.id, "HO%d", rand() % MAX_RAND_ID);

    novoHospital.capacidadeMaxima = rand() % MAX_DISPONIVEIS;

    novoHospital.ocorrenciasAtivas = rand() % MAX_ATIVAS;

    novoHospital.pos.x = rand() % MAX_RAND_POS;

    novoHospital.pos.y = rand() % MAX_RAND_POS;

    return novoHospital;

}


Policia gerarPolicia()
{
    Policia novaPolicia;

    sprintf(novaPolicia.id, "PO%d", rand() % MAX_RAND_ID);

    if(rand() % 2 == 1)
    {
        novaPolicia.emAtendimento = true;

    }else{

        novaPolicia.emAtendimento = false;

    }

    novaPolicia.pos.x = rand() % MAX_RAND_POS;
    novaPolicia.pos.y = rand() % MAX_RAND_POS;

    return novaPolicia;
}

SAMU gerarSAMU()
{
    SAMU novoSamu;

    sprintf(novoSamu.id, "SA%d", rand() % MAX_RAND_ID);

    novoSamu.ambulanciasDisponiveis = rand() % MAX_DISPONIVEIS;

    novoSamu.ambulanciasAtivas = rand() % MAX_ATIVAS;

    novoSamu.pos.x = rand() % MAX_RAND_POS;

    novoSamu.pos.y = rand() % MAX_RAND_POS;

    return novoSamu;
}

