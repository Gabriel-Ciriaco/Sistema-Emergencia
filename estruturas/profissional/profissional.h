#ifndef PROFISSIONAL_H
#define PROFISSIONAL_H

#include "../cidadao/cidadao.h"
#include "../tipos_abstratos/pilha/pilha.h"


typedef struct profissional
{
    Cidadao cidadao;

    Pilha historicoAtendimento;

} Profissional;


#endif // PROFISSIONAL_H
