#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include "../../ocorrencia/ocorrencia.h"

#define MAX_PILHA 100

#include<stdbool.h>

typedef struct
{
    Ocorrencia pilha[MAX_PILHA];
    int topo;
}Pilha;

Pilha criarPilha();

bool estaVaziaPilha(Pilha *pilha);

bool estaCheiaPilha(Pilha *pilha);

void inserirValorPilha(Pilha *pilhaOco, Ocorrencia ocorrencia);

Ocorrencia removerValorPilha(Pilha *pilhaOco);

void destruirPilha(Pilha *pilhaOco);

#endif // PILHA_H_INCLUDED
