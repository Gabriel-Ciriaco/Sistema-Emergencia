#include "pilha.h"

#include<stdbool.h>

Pilha criarPilha()
{
    Pilha pilha;

    pilha.topo = -1;

    return pilha;
}

bool estaVaziaPilha(Pilha *pilha)
{
    return pilha->topo == -1;
}

bool estaCheiaPilha(Pilha *pilha)
{
    return pilha->topo == MAX_PILHA - 1;
}

void inserirValorPilha(Pilha *pilhaOco, Ocorrencia ocorrencia)
{
    if(estaCheiaPilha(pilhaOco))
    {
        return;
    }

    pilhaOco->pilha[++pilhaOco->topo] = ocorrencia;
}

Ocorrencia removerValorPilha(Pilha *pilhaOco)
{
    if(estaVaziaPilha(pilhaOco))
    {
        Ocorrencia vazia;

        strcpy(vazia.id, "");
        vazia.tipo = 0;
        vazia.gravidade = 0;
        strcpy(vazia.horaOcorrencia, "");
        strcpy(vazia.descricao, "");
        vazia.vitima = NULL;
        vazia.responsavel = NULL;

        return vazia;
    }

    Ocorrencia ocorrenciaRemovida = pilhaOco->pilha[pilhaOco->topo--];

    return ocorrenciaRemovida;
}

void destruirPilha(Pilha *pilhaOco)
{
    pilhaOco->topo = -1;
}
