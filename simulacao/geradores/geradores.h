#ifndef GERADORES_H
#define GERADORES_H

#include "../../estruturas/unidades-de-servico/unidadade-de-servico.h"

#include "../../estruturas/bairro/bairro.h"
#include "../../estruturas/cidadao/cidadao.h"

#include "../../estruturas/unidades-de-servico/bombeiro/bombeiro.h"
#include "../../estruturas/unidades-de-servico/hospital/hospital.h"
#include "../../estruturas/unidades-de-servico/policia/policia.h"
#include "../../estruturas/unidades-de-servico/samu/samu.h"

// Alterar o path de acordo com onde a função gerarCidadao for executada!
#define NOMES_CIDADAO_PATH "./estruturas/cidadao/nomes_cidadao.txt"

#define RAND_IDADE 80

Bairro gerarBairro(const char * nome, UnidadeServico unidadeServico);

Cidadao gerarCidadao();

Bombeiro gerarBombeiro();

Hospital gerarHospital(const char * nome);

Policia gerarPolicia();

SAMU gerarSAMU();

#endif // GERADORES_H
