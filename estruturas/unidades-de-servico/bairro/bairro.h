#ifndef BAIRRO_H
#define BAIRRO_H

#include "../../../constantes-sistema/constantes-sistema.h"

#include "../../vetoriais/posicao.h"



typedef struct{

    char id[MAX_ID];
    char nome[MAX_NOME];

    typedef union{

        Hospital hospital;
        SAMU samu;
        Bombeiro bombeiro;
        Policia policia;

    }unidadesServico;

    Posicao pos;

}Bairro;

#endif
