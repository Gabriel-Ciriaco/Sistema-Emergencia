#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "../../../constantes-sistema/constantes-sistema.h"

#include "../../vetoriais/posicao.h"


typedef struct{

    char id[MAX_ID];
    char nome[MAX_NOME];
    int capacidadeMaxima;
    int ocorrenciasAtivas;

    Posicao pos;

}Hospital;


#endif
