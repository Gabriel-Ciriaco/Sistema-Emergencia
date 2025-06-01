#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include "../../../constantes-sistema/constantes-sistema.h"

#include "../../bairro/bairro.h"

#include "../../cidadao/cidadao.h"

#include "../../unidades-de-servico/unidadade-de-servico.h"


#define MAX_TABELA_HASH 100
#define CHAVE_NULA ""

typedef enum
{
    HASH_BAIRRO,
    HASH_CIDADAO,
    HASH_UNIDADE_SERVICO,
} TipoElementoHash;

typedef union valorHash
{
    Bairro bairro;
    Cidadao cidadao;
    UnidadeServico unidadeServico;
} ValorHash;

typedef struct noHash
{
    char chave[MAX_ID];

    ValorHash valor;

    struct noHash * prox;
} NoHash;


typedef struct tabelaHash
{
    TipoElementoHash tipo;

    NoHash *tabela[MAX_TABELA_HASH];

} TabelaHash;

NoHash *criarNoHash(const char * chave, ValorHash valor);

TabelaHash criarTabelaHash(TipoElementoHash tipo);

int funcaoHash(const char * chave);

void inserirValorTabela(TabelaHash * tabelaH,
                        const char * chave,
                        ValorHash valor);

void removerValorTabela(TabelaHash * tabelaH,
                        const char * chave);

ValorHash * buscaValorTabela(TabelaHash * tabelaH,
                             const char * chave);

void limparTabela(TabelaHash * tabelaH);

#endif // TABELA_HASH_H
