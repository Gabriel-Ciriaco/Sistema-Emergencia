#ifndef CIDADAO_H
#define CIDADAO_H

#include "../../constantes-sistema/constantes-sistema.h"

#include "../bairro/bairro.h"

#include "../vetoriais/posicao.h"


#define CPF_SIZE 15

#define MAX_TELEFONE 16


typedef struct cidadao
{
    char id[MAX_ID];

    char nome[MAX_NOME];

    int idade;

    char cpf[CPF_SIZE];

    char telefoneEmergencia[MAX_TELEFONE];

    Bairro * bairro;

    Posicao pos; // Endereço

} Cidadao;


#endif // CIDADAO_H
