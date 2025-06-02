#include "geradores.h"
#include "texto_aleatorio.h"

#include "../../constantes-sistema/constantes-sistema.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

Bairro gerarBairro(const char * nome, UnidadeServico unidadeServico)
{
    Bairro novoBairro;

    strcpy(novoBairro.nome, nome);

    sprintf(novoBairro.id, "BA%d", rand() % MAX_RAND_ID);

    novoBairro.pos.x = rand() % MAX_RAND_POS;

    novoBairro.pos.y = rand() % MAX_RAND_POS;

    return novoBairro;
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

    sprintf(telefone, "(%02d) %d%d%d%d%d-%d%d%d%d",
            DDD,
            numero[0], numero[1], numero[2], numero[3], numero[4],
            numero[5], numero[6], numero[7], numero[8]);

    telefone[MAX_TELEFONE - 1] = '\0'; // Garantia que a string finalizou corretamente.
}

Cidadao gerarCidadao()
{
    Cidadao novoCidadao;

    textoAleatorio(&novoCidadao.nome, NOMES_CIDADAO_PATH);

    sprintf(novoCidadao.id, "CD%d", rand() % MAX_RAND_ID);

    novoCidadao.idade = rand() % RAND_IDADE;

    cpfAleatorio(novoCidadao.cpf);

    telefoneAleatorio(novoCidadao.telefoneEmergencia);

    return novoCidadao;

}

Ocorrencia gerarOcorrencia(char * horaOcorrencia,
                           Cidadao * vitima,
                           Cidadao * responsavel)
{
    Ocorrencia novaOcorrencia;

    sprintf(novaOcorrencia.id, "OC%d", rand() % MAX_RAND_ID);

    novaOcorrencia.tipo = rand() % NUM_TIPOS_OCORRENCIA;

    strcpy(novaOcorrencia.horaOcorrencia, horaOcorrencia);

    novaOcorrencia.vitima = vitima;

    novaOcorrencia.responsavel = responsavel;

    switch(novaOcorrencia.tipo)
    {
        case OCORRENCIA_BOMBEIRO:
            textoAleatorio(&novaOcorrencia.descricao, OCORRENCIAS_BOMBEIRO_PATH);
        break;

        case OCORRENCIA_HOSPITAL:
            textoAleatorio(&novaOcorrencia.descricao, OCORRENCIAS_HOSPITAL_PATH);
        break;

        case OCORRENCIA_POLICIA:
            textoAleatorio(&novaOcorrencia.descricao, OCORRENCIAS_POLICIA_PATH);
        break;
    }

    int tamanhoDescricao = strlen(novaOcorrencia.descricao);

    /*
        A gravidade da ocorrência é armazenada no final da descrição.

        Assim, como pode ser um valor de 0-3, subtraímos '0' do caracter
        que é o número da gravidade e o convertemos para int.
    */
    novaOcorrencia.gravidade = (int) novaOcorrencia.descricao[tamanhoDescricao - 1] - '0';

    // Retiramos o valor da gravidade da ocorrência da descrição.
    novaOcorrencia.descricao[tamanhoDescricao - 1] = '\0';

    return novaOcorrencia;
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

