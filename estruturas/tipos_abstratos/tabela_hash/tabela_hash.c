#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabela_hash.h"


NoHash *criarNo(const char * chave, TipoElementoHash tipo, ValorHash valor)
{
    NoHash *novoNo = (NoHash*)malloc(1 *sizeof(NoHash));

    if(novoNo == NULL)
    {
        return NULL;
    }

    strcpy(novoNo->chave, chave);

    novoNo->tipo = tipo;

    novoNo->valor = valor;

    novoNo->prox = NULL;

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

int funcaoHash(const char * chave)
{
    int indice = 0;

    for(int i=0; i<strlen(chave); i++)
    {
        indice += i * chave[i];
    }

    return (indice % MAX_TABELA_HASH);
}

void inserirValor(TabelaHash * tabelaH, const char * chave, TipoElementoHash tipo, ValorHash valor)
{
    int indiceTabela = funcaoHash(chave);

    NoHash *atual = tabelaH[indiceTabela];
    NoHash *anterior = NULL;

    while(atual != NULL && (strcasecmp(atual->chave, chave) != 0))
    {
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL)
    {
        NoHash *novoNo = criarNo(chave, tipo, valor);

        if(novoNo == NULL) //Deu algum erro ao alocar memória.
        {
            return;
        }

        //A posição da tabela está vazia.
        if(anterior == NULL)
        {
            tabelaH[indiceTabela] = novoNo;

        //Houve colisão
        }else{

            anterior->prox = novoNo;
        }
    }
}

void removerValor(TabelaHash * tabelaH, const char * chave, TipoElementoHash tipo, ValorHash valor)
{
    int indiceTabela = funcaoHash(chave);

    NoHash *atual = tabelaH[indiceTabela];
    NoHash *anterior = NULL;

    while(atual != NULL && (strcasecmp(atual->chave, chave) != 0))
    {
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL) //Nao há nenhum elemento armazenado naquela posicão da tabela ou o elemento não foi encontrado.
    {
        return;
    }

    //Elemento a ser removido foi encontrado.

    if(anterior == NULL) //Ele é logo o primeiro elemento.
    {
        tabelaH[indiceTabela] = atual->prox;

    }else{

        anterior->prox = atual->prox;
    }

    free(atual);

}


