#ifndef POLICIA_H
#define POLICIA_H

#include "../../../constantes-sistema/constantes-sistema.h"

#include "../../vetoriais/posicao.h"

typedef struct policia
{
    char id[MAX_ID];

    Posicao pos;

} Policia;

#endif // POLICIA_H
