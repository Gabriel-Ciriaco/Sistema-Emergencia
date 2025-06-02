#ifndef OCORRENCIA_H
#define OCORRENCIA_H

#include "../../constantes-sistema/constantes-sistema.h"

#include "../vetoriais/posicao.h"

#include "../cidadao/cidadao.h"


#include <time.h>

#define NUM_TIPOS_OCORRENCIA 3

#define NUM_GRAVIDADES 3

#define MAX_DESCRICAO 100

#define HORA_OCORRENCIA 9

typedef enum tipoOcorrencia
{
    OCORRENCIA_BOMBEIRO,
    OCORRENCIA_HOSPITAL,
    OCORRENCIA_POLICIA,
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

    char horaOcorrencia[HORA_OCORRENCIA];

    char descricao[MAX_DESCRICAO];

    Cidadao * vitima;

    Cidadao * responsavel; // Responsável pelo acidente (pode ser NULL).

} Ocorrencia;

#endif // OCORRENCIA_H
