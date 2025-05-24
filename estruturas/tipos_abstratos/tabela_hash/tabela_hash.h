#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include "../../../../constantes-sistema/constantes-sistema.h"

#include "../../bairro/bairro.h"

#include "../../../cidadao/cidadao.h"

#include "../../unidadade-de-servico.h"


#define MAX_TABELA_HASH 100
#define CHAVE_NULA ""

typedef enum
{
    ELEMENTO_HASH_NULO,
    BAIRRO,
    CIDADAO,
    UNIDADE_SERVICO,
} TipoElementoHash;

typedef union valorHash
{
    Bairro * bairro;
    Cidadao * cidadao;
    UnidadeServico * unidadeServico;
} ValorHash;

typedef struct noHash
{
    char chave[MAX_ID];

    TipoElementoHash tipo;

    ValorHash valor;

    struct noHash * prox;
} NoHash;


typedef tabelaHash
{
    NoHash *tabela[MAX_TABELA_HASH];

} TabelaHash;

NoHash *criarNo(const char * chave, TipoElementoHash tipo, ValorHash valor);

NoHash criarNoVazio();

TabelaHash criarTabelaHash();

int funcaoHash(const char * chave);

void inserirValor(TabelaHash * tabelaH,
                  const char * chave,
                  TipoElementoHash tipo,
                  ValorHash valor);

void removerValor(TabelaHash * tabelaH,
                  const char * chave,
                  TipoElementoHash tipo,
                  ValorHash valor);
#endif // TABELA_HASH_H
