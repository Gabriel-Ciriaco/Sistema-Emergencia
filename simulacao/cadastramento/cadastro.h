#ifndef CADASTRO_H
#define CADASTRO_H

#include "../../estruturas/tipos_abstratos/tabela_hash/tabela_hash.h"

#include "../../estruturas/unidades-de-servico/bairro/bairro.h"
#include "../../estruturas/unidades-de-servico/bombeiro/bombeiro.h"
#include "../../estruturas/unidades-de-servico/hospital/hospital.h"
#include "../../estruturas/unidades-de-servico/policia/policia.h"
#include "../../estruturas/unidades-de-servico/samu/samu.h"


Bairro cadastrarBairro(TabelaHash * bairros, Bairro bairro);

Bombeiro cadastrarBombeiro(TabelaHash * bombeiros, Bombeiro bombeiro);

Hospital cadastrarHospital(TabelaHash * hospitais, Hospital hospital);

Policia cadastrarPolicia(TabelaHash * policias, Policia policia);

SAMU cadastrarSAMU(TabelaHash * samus, SAMU samu);

#endif // CADASTRO_H
