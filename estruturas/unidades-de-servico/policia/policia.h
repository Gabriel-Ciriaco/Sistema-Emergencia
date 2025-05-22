#ifndef POLICIA_H
#define POLICIA_H

#include "../../../constantes-sistema/constantes-sistema.h"

#include "../../vetoriais/posicao.h"


#include <stdbool.h>


typedef struct policia
{
    char id[MAX_ID];

    bool emAtendimento;

    Posicao pos;

} Policia;

#endif // POLICIA_H
