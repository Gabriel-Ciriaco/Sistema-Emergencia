#ifndef CADASTRO_H
#define CADASTRO_H

#include "../../estruturas/tipos_abstratos/tabela_hash/tabela_hash.h"

#include "../../estruturas/bairro/bairro.h"
#include "../../estruturas/cidadao/cidadao.h"

#include "../../estruturas/unidades-de-servico/bombeiro/bombeiro.h"
#include "../../estruturas/unidades-de-servico/hospital/hospital.h"
#include "../../estruturas/unidades-de-servico/policia/policia.h"
#include "../../estruturas/unidades-de-servico/samu/samu.h"


void cadastrarBairro(TabelaHash * bairros, Bairro bairro);

Bairro * resgatarCadastroBairro(TabelaHash * bairros,
                                const char * bairroId);


void cadastrarCidadao(TabelaHash * cidadaos, Cidadao cidadao);

Cidadao * resgatarCadastroCidadao(TabelaHash * cidadaos,
                                  const char * cidadaoId);


void cadastrarBombeiro(TabelaHash * bombeiros, Bombeiro bombeiro);

Bombeiro * resgatarCadastroBombeiro(TabelaHash * bombeiros,
                                    const char * bombeiroId);


void cadastrarHospital(TabelaHash * hospitais, Hospital hospital);

Hospital * resgatarCadastroHospital(TabelaHash * hospitais,
                                    const char * hospitalId);


void cadastrarPolicia(TabelaHash * policias, Policia policia);

Policia * resgatarCadastroPolicia(TabelaHash * policias,
                                  const char * policiaId);


void cadastrarSAMU(TabelaHash * samus, SAMU samu);

SAMU * resgatarCadastroSAMU(TabelaHash * samus,
                            const char * samuId);

#endif // CADASTRO_H
