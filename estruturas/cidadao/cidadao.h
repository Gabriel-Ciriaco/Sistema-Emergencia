#ifndef CIDADAO_H
#define CIDADAO_H

#include "../../constantes-sistema/constantes-sistema.h"

#include "../vetoriais/posicao.h"


#define CPF_SIZE 11

#define MAX_EMAIL 50

typedef struct cidadao
{
    char id[MAX_ID];

    char nome[MAX_NOME];

    char cpf[CPF_SIZE];

    char email[MAX_EMAIL];

    Bairro * bairro;

    Posicao pos; // Endereço

} Cidadao;


#endif // CIDADAO_H
