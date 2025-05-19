#ifndef OCORRENCIA_H
#define OCORRENCIA_H

#include "../../constantes-sistema/constantes-sistema.h"
#include "../vetoriais/posicao.h"

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

} Ocorrencia;

#endif // OCORRENCIA_H
