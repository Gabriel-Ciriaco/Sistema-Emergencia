#ifndef GERADORES_H
#define GERADORES_H

#include "../../estruturas/unidades-de-servico/unidadade-de-servico.h"

#include "../../estruturas/unidades-de-servico/bairro/bairro.h"
#include "../../estruturas/unidades-de-servico/bombeiro/bombeiro.h"
#include "../../estruturas/unidades-de-servico/hospital/hospital.h"
#include "../../estruturas/unidades-de-servico/policia/policia.h"
#include "../../estruturas/unidades-de-servico/samu/samu.h"

Bairro gerarBairro(const char * nome, UnidadeServico unidadeServico);

Bombeiro gerarBombeiro();

Hospital gerarHospital(const char * nome);

Policia gerarPolicia();

SAMU gerarSAMU();

#endif // GERADORES_H
