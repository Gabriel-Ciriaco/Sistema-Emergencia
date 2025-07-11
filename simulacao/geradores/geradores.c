#include "geradores.h"
#include "texto_aleatorio.h"

#include "../../constantes-sistema/constantes-sistema.h"

#include "../../estruturas/vetoriais/posicao.h"

#include "../../estruturas/tipos_abstratos/pilha/pilha.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


Bairro gerarBairro()
{
    Bairro novoBairro;

    textoAleatorio(novoBairro.nome, NOMES_BAIRRO_PATH);

    sprintf(novoBairro.id, "BA%d", rand() % MAX_RAND_ID);

    posicaoAleatoria(&novoBairro.pos);

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
    // DDD entre 10 e 90. Escolha arbitr�ria.
    int DDD = rand() % 90 + 10;

    const int QUANTIDADE_DIGITOS = 9;

    int numero[QUANTIDADE_DIGITOS];

    numero[0] = 9; // Primeiro d�gito � sempre nove.

    for (int i = 1; i < QUANTIDADE_DIGITOS; i++)
    {
        numero[i] = rand() % 10;
    }

    sprintf(telefone, "(+%02d) %d%d%d%d%d-%d%d%d%d",
            DDD,
            numero[0], numero[1], numero[2], numero[3], numero[4],
            numero[5], numero[6], numero[7], numero[8]);

    telefone[MAX_TELEFONE - 1] = '\0'; // Garantia que a string finalizou corretamente.
}

Cidadao gerarCidadao()
{
    Cidadao novoCidadao;

    textoAleatorio(novoCidadao.nome, NOMES_CIDADAO_PATH);

    sprintf(novoCidadao.id, "CD%d", rand() % MAX_RAND_ID);

    novoCidadao.idade = rand() % RAND_IDADE;

    cpfAleatorio(novoCidadao.cpf);

    telefoneAleatorio(novoCidadao.telefoneEmergencia);

    posicaoAleatoria(&novoCidadao.pos);

    return novoCidadao;

}

Profissional gerarProfissional()
{
    Cidadao profissionalCidadao = gerarCidadao();

    Profissional novoProfissional;

    novoProfissional.cidadao = profissionalCidadao;

    novoProfissional.historicoAtendimento = criarPilha();

    textoAleatorio(novoProfissional.cidadao.nome, NOMES_PROFISSIONAL_PATH);

    return novoProfissional;
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

    novaOcorrencia.responsavel = NULL; // S� ser� alterada se for caso de pol�cia.

    switch(novaOcorrencia.tipo)
    {
        case OCORRENCIA_BOMBEIRO:
            textoAleatorio(novaOcorrencia.descricao, OCORRENCIAS_BOMBEIRO_PATH);
        break;

        case OCORRENCIA_HOSPITAL:
            textoAleatorio(novaOcorrencia.descricao, OCORRENCIAS_HOSPITAL_PATH);
        break;

        case OCORRENCIA_POLICIA:

            novaOcorrencia.responsavel = responsavel;

            textoAleatorio(novaOcorrencia.descricao, OCORRENCIAS_POLICIA_PATH);
        break;
    }

    int tamanhoDescricao = strlen(novaOcorrencia.descricao);

    /*
        A gravidade da ocorr�ncia � armazenada no final da descri��o.

        Assim, como pode ser um valor de 0-3, subtra�mos '0' do caracter
        que � o n�mero da gravidade e o convertemos para int.
    */
    novaOcorrencia.gravidade = (int) novaOcorrencia.descricao[tamanhoDescricao - 1] - '0';

    // Retiramos o valor da gravidade da ocorr�ncia da descri��o.
    novaOcorrencia.descricao[tamanhoDescricao - 1] = '\0';

    return novaOcorrencia;
}

Bombeiro gerarBombeiro()
{
    Bombeiro novoBombeiro;

    sprintf(novoBombeiro.id, "BO%d", rand() % MAX_RAND_ID);

    novoBombeiro.emAtendimento = (rand() % 2 == 1);

    posicaoAleatoria(&novoBombeiro.pos);

    return novoBombeiro;
}


Hospital gerarHospital()
{
    Hospital novoHospital;

    sprintf(novoHospital.id, "HO%d", rand() % MAX_RAND_ID);

    novoHospital.capacidadeMaxima = rand() % MAX_DISPONIVEIS;

    novoHospital.ocorrenciasAtivas = rand() % MAX_ATIVAS;

    posicaoAleatoria(&novoHospital.pos);

    return novoHospital;

}


Policia gerarPolicia()
{
    Policia novaPolicia;

    sprintf(novaPolicia.id, "PO%d", rand() % MAX_RAND_ID);

    novaPolicia.emAtendimento = (rand() % 2 == 1);

    posicaoAleatoria(&novaPolicia.pos);

    return novaPolicia;
}

SAMU gerarSAMU()
{
    SAMU novoSamu;

    sprintf(novoSamu.id, "SA%d", rand() % MAX_RAND_ID);

    novoSamu.ambulanciasDisponiveis = rand() % MAX_DISPONIVEIS;

    novoSamu.ambulanciasAtivas = rand() % MAX_ATIVAS;

    posicaoAleatoria(&novoSamu.pos);

    return novoSamu;
}

