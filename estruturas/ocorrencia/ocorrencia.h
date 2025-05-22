#ifndef OCORRENCIA_H
#define OCORRENCIA_H

#include "../../constantes-sistema/constantes-sistema.h"

#include "../vetoriais/posicao.h"

#include "../cidadao/cidadao.h"


#include <time.h>


#define MAX_DESCRICAO 100


typedef enum tipoOcorrencia
{
    BOMBEIRO,
    POLICIA,
    HOSPITAL,
} TipoOcorrencia;

typedef enum gravidade
{
    BAIXA,
    MEDIA,
    ALTA,
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
