#ifndef UNIDADADE_DE_SERVICO_H
#define UNIDADADE_DE_SERVICO_H

#include "bombeiro/bombeiro.h"
#include "hospital/hospital.h"
#include "policia/policia.h"
#include "samu/samu.h"

typedef union unidadeServico
{
    Bombeiro bombeiro;
    Hospital hospital;
    Policia policia;
    SAMU samu;
} UnidadeServico;


#endif // UNIDADADE_DE_SERVICO_H
