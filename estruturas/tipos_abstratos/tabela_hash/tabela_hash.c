#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabela_hash.h"


NoHash criarNo(const char * chave, TipoElementoHash tipo, ValorHash valor)
{
    NoHash novoNo;

    strcpy(novoNo.chave, chave);

    novoNo.tipo = tipo;

    novoNo.valor = valor;

    novoNo.prox = NULL;

    return novoNo;
}

NoHash criarNoVazio()
{
    NoHash noVazio;


    strcpy(noVazio.chave, CHAVE_NULA);


    noVazio.tipo = ELEMENTO_HASH_NULO;

    /*
        Como o valor é uma union, qualquer campo
        que limparmos, deixará a union vazia.
    */
    noVazio.valor.bairro = NULL;

    noVazio.prox = NULL;


    return noVazio;
}

TabelaHash criarTabelaHash()
{
    TabelaHash novaTabela;

    for (int i = 0; i < MAX_TABELA_HASH; i++)
    {
        novaTabela.tabela[i] = criarNoVazio();
    }

    return novaTabela;
}
