#include "geradores.h"
#include "../../constantes-sistema/constantes-sistema.h"

#include<string.h>
#include<stdlib.h>

Bairro gerarBairro(const char * nome, UnidadeServico unidadeServico)
{

    Bairro novoBairro;

    strcpy(novoBairro.nome, nome);

    sprintf(novoBairro.id, "BA%d", rand() % MAX_RAND_ID);

    novoBairro.unidadeServico = unidadeServico;

    novoBairro.pos.x = rand() % MAX_RAND_POS;

    novoBairro.pos.y = rand() % MAX_RAND_POS;

    return novoBairro;
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

