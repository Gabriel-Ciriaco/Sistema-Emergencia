#ifndef OCORRENCIA_H
#define OCORRENCIA_H

#include "../../constantes-sistema/constantes-sistema.h"

#include "../vetoriais/posicao.h"

#include "../cidadao/cidadao.h"


#include <time.h>


#define MAX_DESCRICAO 100


typedef enum tipoOcorrencia
{
    OCORRENCIA_BOMBEIRO,
    OCORRENCIA_POLICIA,
    OCORRENCIA_HOSPITAL,
} TipoOcorrencia;

typedef enum gravidade
{
    GRAVIDADE_BAIXA,
    GRAVIDADE_MEDIA,
    GRAVIDADE_ALTA,
} Gravidade;

typedef struct ocorrencia
{
    char id[MAX_ID];

    TipoOcorrencia tipo;

    Gravidade gravidade;

    struct tm horaOcorrencia;

    char descricao[MAX_DESCRICAO];

    Cidadao * vitima;

    Cidadao * responsavel; // Responsável pelo acidente (pode ser NULL).

} Ocorrencia;

#endif // OCORRENCIA_H
