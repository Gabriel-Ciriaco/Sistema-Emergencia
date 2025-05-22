#ifndef BOMBEIRO_H
#define BOMBEIRO_H

#include "../../../constantes-sistema/constantes-sistema.h"

#include "../../vetoriais/posicao.h"


#include <stdbool.h>


typedef struct bombeiro
{
    char id[MAX_ID];

    bool emAtendimento;

    Posicao pos;
} Bombeiro;

#endif // BOMBEIRO_H
