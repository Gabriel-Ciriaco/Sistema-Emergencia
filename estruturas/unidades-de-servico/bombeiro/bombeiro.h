#ifndef BOMBEIRO_H
#define BOMBEIRO_H

#include "../../../constantes-sistema/constantes-sistema.h"

#include "../../vetoriais/posicao.h"

typedef struct bombeiro
{
    char id[MAX_ID];

    Posicao pos;
} Bombeiro;

#endif // BOMBEIRO_H
