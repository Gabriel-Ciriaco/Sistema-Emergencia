#ifndef GERADORES_H
#define GERADORES_H

#include "../../estruturas/unidades-de-servico/unidadade-de-servico.h"

#include "../../estruturas/bairro/bairro.h"
#include "../../estruturas/cidadao/cidadao.h"

#include "../../estruturas/ocorrencia/ocorrencia.h"

#include "../../estruturas/unidades-de-servico/bombeiro/bombeiro.h"
#include "../../estruturas/unidades-de-servico/hospital/hospital.h"
#include "../../estruturas/unidades-de-servico/policia/policia.h"
#include "../../estruturas/unidades-de-servico/samu/samu.h"

#include <time.h>

// Alterar o PATH de acordo com onde a função de geração for executada!
#define NOMES_CIDADAO_PATH "./estruturas/cidadao/nomes_cidadao.txt"

#define OCORRENCIAS_BOMBEIRO_PATH "./estruturas/ocorrencia/ocorrencias_bombeiro.txt"

#define OCORRENCIAS_HOSPITAL_PATH "./estruturas/ocorrencia/ocorrencias_hospital.txt"

#define OCORRENCIAS_POLICIA_PATH "./estruturas/ocorrencia/ocorrencias_policia.txt"
//
#define RAND_IDADE 80

Bairro gerarBairro(const char * nome, UnidadeServico unidadeServico);

Cidadao gerarCidadao();

Ocorrencia gerarOcorrencia(char * horaOcorrencia,
                           Cidadao * vitima,
                           Cidadao * responsavel);

Bombeiro gerarBombeiro();

Hospital gerarHospital(const char * nome);

Policia gerarPolicia();

SAMU gerarSAMU();

#endif // GERADORES_H
