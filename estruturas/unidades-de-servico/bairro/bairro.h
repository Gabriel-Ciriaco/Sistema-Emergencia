#ifndef BAIRRO_H
#define BAIRRO_H

#include "../../../constantes-sistema/constantes-sistema.h"

#include "../../vetoriais/posicao.h"

#include "../unidadade-de-servico.h"



typedef struct{

    char id[MAX_ID];
    char nome[MAX_NOME];

    UnidadeServico unidadeServico;

    Posicao pos;

}Bairro;

#endif
