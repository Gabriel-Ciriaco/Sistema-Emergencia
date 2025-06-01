#include "tabela_hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


NoHash *criarNo(const char * chave, ValorHash valor)
{
    NoHash *novoNo = (NoHash*)malloc(1 *sizeof(NoHash));

    if(novoNo == NULL)
    {
        return NULL;
    }

    strcpy(novoNo->chave, chave);

    novoNo->valor = valor;

    novoNo->prox = NULL;

    return novoNo;
}

TabelaHash criarTabelaHash(TipoElementoHash tipo)
{
    TabelaHash novaTabela;

    novaTabela.tipo = tipo;

    for (int i = 0; i < MAX_TABELA_HASH; i++)
    {
        novaTabela.tabela[i] = NULL;
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

void inserirValorTabela(TabelaHash * tabelaH, const char * chave, ValorHash valor)
{
    int indiceTabela = funcaoHash(chave);

    NoHash *atual = tabelaH->tabela[indiceTabela];
    NoHash *anterior = NULL;

    while(atual != NULL && (strcasecmp(atual->chave, chave) != 0))
    {
        anterior = atual;
        atual = atual->prox;
    }


    if(atual == NULL)
    {
        NoHash *novoNo = criarNo(chave, valor);

        if(novoNo == NULL) //Deu algum erro ao alocar memória.
        {
            return;
        }

        //A posição da tabela está vazia.
        if(anterior == NULL)
        {
            tabelaH->tabela[indiceTabela] = novoNo;

        //Houve colisão
        }else{

            anterior->prox = novoNo;
        }
    }

}

void removerValorTabela(TabelaHash * tabelaH, const char * chave)
{
    int indiceTabela = funcaoHash(chave);

    NoHash *atual = tabelaH->tabela[indiceTabela];
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
        tabelaH->tabela[indiceTabela] = atual->prox;

    }else{

        anterior->prox = atual->prox;
    }

    free(atual);

}

ValorHash * buscaValorTabela(TabelaHash * tabelaH, const char * chave)
{
    int indiceTabela = funcaoHash(chave);

    NoHash *atual = tabelaH->tabela[indiceTabela];

    while (atual != NULL)
    {
        if (strcasecmp(atual->chave, chave) == 0)
        {
            return &(atual->valor);
        }

        atual = atual->prox;
    }

    return NULL;
}

void limparTabela(TabelaHash * tabelaH)
{
    for (int i = 0; i < MAX_TABELA_HASH; i++)
    {
        NoHash * elemento = tabelaH->tabela[i];

        removerValorTabela(tabelaH, elemento->chave);

        free(elemento);

        tabelaH->tabela[i] = NULL;
    }
}
