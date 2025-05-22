#ifndef UNIDADADE-DE-SERVICO_H
#define UNIDADADE-DE-SERVICO_H

#include "bombeiro/bombeiro.h"
#include "hospital/hospital.h"
#include "policia/policia.h"
#include "samu/samu.h"

typedef union unidadeServico
{
    Bombeiro bombeiro;
    Hospital hospital;
    Policia policia;
    Samu samu;
} UnidadeServico;


#endif // UNIDADADE-DE-SERVICO_H
