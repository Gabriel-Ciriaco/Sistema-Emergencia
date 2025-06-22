#ifndef BAIRRO_H
#define BAIRRO_H

#include "../../constantes-sistema/constantes-sistema.h"

#include "../vetoriais/posicao.h"


typedef struct{

    char id[MAX_ID];
    char nome[MAX_NOME];

    Posicao pos;

}Bairro;

#endif
