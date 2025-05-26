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

void inserirValor(TabelaHash * tabelaH, const char * chave, ValorHash valor)
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
        NoHash *novoNo = criarNo(chave, valor);

        if(novoNo == NULL) //Deu algum erro ao alocar mem�ria.
        {
            return;
        }

        //A posi��o da tabela est� vazia.
        if(anterior == NULL)
        {
            tabelaH[indiceTabela] = novoNo;

        //Houve colis�o
        }else{

            anterior->prox = novoNo;
        }
    }
}

void removerValor(TabelaHash * tabelaH, const char * chave, ValorHash valor)
{
    int indiceTabela = funcaoHash(chave);

    NoHash *atual = tabelaH[indiceTabela];
    NoHash *anterior = NULL;

    while(atual != NULL && (strcasecmp(atual->chave, chave) != 0))
    {
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL) //Nao h� nenhum elemento armazenado naquela posic�o da tabela ou o elemento n�o foi encontrado.
    {
        return;
    }

    //Elemento a ser removido foi encontrado.

    if(anterior == NULL) //Ele � logo o primeiro elemento.
    {
        tabelaH[indiceTabela] = atual->prox;

    }else{

        anterior->prox = atual->prox;
    }

    free(atual);

}

void limparTabela(TabelaHash * tabelaH)
{
    for (int i = 0; i < MAX_TABELA_HASH; i++)
    {
        NoHash * elemento = tabelaH.tabela[i];

        removerValor(tabelaH, elemento->chave, elemento->valor);

        free(elemento);

        tabelaH.tabela[i] = NULL;
    }
}
