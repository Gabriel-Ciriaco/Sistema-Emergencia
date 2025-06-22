#ifndef SAMU_H
#define SAMU_H

#include "../../../constantes-sistema/constantes-sistema.h"

#include "../../vetoriais/posicao.h"


typedef struct{

    char id[MAX_ID];

    int ambulanciasDisponiveis;
    int ambulanciasAtivas;

    Posicao pos;
}SAMU;


#endif
