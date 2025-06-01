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
    if (NOMES_PATH == NULL) return -1;

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

void cpfAleatorio(char * cpf)
{
    const int QTD_NUM_CPF = 11;

    int cpfNumeros[QTD_NUM_CPF];

    for (int i = 0; i < QTD_NUM_CPF; i++)
    {
        cpfNumeros[i] = rand() % 10;
    }

    sprintf(cpf, "%d%d%d.%d%d%d.%d%d%d-%d%d",
            cpfNumeros[0], cpfNumeros[1], cpfNumeros[2],
            cpfNumeros[3], cpfNumeros[4], cpfNumeros[5],
            cpfNumeros[6], cpfNumeros[7], cpfNumeros[8],
            cpfNumeros[9], cpfNumeros[10]);

    cpf[CPF_SIZE - 1] = '\0'; // Garantia que a string finalizou corretamente.
}

void telefoneAleatorio(char * telefone)
{
    // DDD entre 10 e 90. Escolha arbitrária.
    int DDD = rand() % 90 + 10;

    const int QUANTIDADE_DIGITOS = 9;

    int numero[QUANTIDADE_DIGITOS];

    numero[0] = 9; // Primeiro dígito é sempre nove.

    for (int i = 1; i < QUANTIDADE_DIGITOS; i++)
    {
        numero[i] = rand() % 10;
    }

    sprintf(telefone, "(%02d) %d%d%d%d%d%d%d%d%d",
            DDD,
            numero[0], numero[1], numero[2], numero[3], numero[4],
            numero[5], numero[6], numero[7], numero[8]);

    telefone[MAX_TELEFONE - 1] = '\0'; // Garantia que a string finalizou corretamente.
}

Cidadao gerarCidadao()
{
    Cidadao novoCidadao;

    nomeCidadaoAleatorio(&novoCidadao.nome);

    sprintf(novoCidadao.id, "CD%d", rand() % MAX_RAND_ID);

    novoCidadao.idade = rand() % RAND_IDADE;

    cpfAleatorio(novoCidadao.cpf);

    telefoneAleatorio(novoCidadao.telefoneEmergencia);

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

