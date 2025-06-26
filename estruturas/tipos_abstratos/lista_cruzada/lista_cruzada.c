#include "lista_cruzada.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../../constantes-sistema/constantes-sistema.h"

ListaCruzada criarListaCruzada()
{
    ListaCruzada listaC;

    for(int i=0; i < NUM_COLUNAS; i++)
    {
        listaC.vetorCol[i] = NULL;
    }

    for(int j=0; j < MAX_BAIRROS; j++)
    {
        listaC.vetorLin[j] = NULL;
    }

    return listaC;
}


NoListaC *criarNoListaCruzada(const char *idBairo, const char *idUnidadeServico, int lin, int col)
{
    NoListaC *novoNo = (NoListaC*)malloc(1*sizeof(NoListaC));

    if(novoNo == NULL)
    {
        return NULL;
    }

    strcpy(novoNo->idBairro, idBairo);
    strcpy(novoNo->idUnidadeServico, idUnidadeServico);

    novoNo->lin = lin;
    novoNo->col = col;

    novoNo->proxLin = NULL;
    novoNo->proxCol = NULL;

    return novoNo;
}


void inserirValorListaCruzada(ListaCruzada *listaC, TipoUnidadeServico tipo, const char *idBairro, const char *idUnidadeServico)
{
    int linha = -1;

    int coluna = tipo;

    for(int i=0; i < MAX_BAIRROS; i++)
    {

        if((listaC->vetorLin[i] != NULL) && (strcmp(listaC->vetorLin[i]->idBairro, idBairro) == 0))
        {
            linha = i;
            break;
        }
    }

    if(linha == -1)
    {
        for(int i =0; i < MAX_BAIRROS; i++)
        {
            if(listaC->vetorLin[i] == NULL)
            {
                linha = i;
                break;
            }
        }
    }

    if(linha == -1)
    {
        printf("\nA lista cruzada ja esta cheia!\n");
        return;
    }

    NoListaC *ptrLin = listaC->vetorLin[linha];
    NoListaC *antLin = NULL;

    while(ptrLin != NULL && ptrLin->col < coluna)
    {
        antLin = ptrLin;
        ptrLin = ptrLin->proxLin;
    }

    //Já possui, nesse bairro, a unidade de serviço que deseja-se inserir.
    if(ptrLin != NULL && ptrLin->col == coluna)
    {
        return;
    }

    NoListaC *novoNo = criarNoListaCruzada(idBairro, idUnidadeServico, linha, coluna);

    if(novoNo == NULL)
    {
        printf("\nErro na alocação de memória!\n");
        return;
    }

    //Insere no começo.
    if(antLin == NULL)
    {
        novoNo->proxLin = listaC->vetorLin[linha];
        listaC->vetorLin[linha] = novoNo;
    }
    //Insere no meio ou no fim.
    else
    {
        novoNo->proxLin = antLin->proxLin;
        antLin->proxLin = novoNo;
    }

    NoListaC *ptrCol = listaC->vetorCol[coluna];
    NoListaC *antCol = NULL;

    while(ptrCol != NULL && ptrCol->lin < linha)
    {
        antCol = ptrCol;
        ptrCol = ptrCol->proxCol;
    }

    if(antCol == NULL)
    {
        novoNo->proxCol = listaC->vetorCol[coluna];
        listaC->vetorCol[coluna] = novoNo;
    }
    else
    {
        novoNo->proxCol = antCol->proxCol;
        antCol->proxCol = novoNo;
    }
}

void removerValorListaCruzada(ListaCruzada *listaC, TipoUnidadeServico tipo, const char *idBairro)
{
    int linha = -1;
    int coluna = tipo;

    for(int i=0; i < MAX_BAIRROS; i++)
    {
        if(listaC->vetorLin[i] != NULL && strcmp(listaC->vetorLin[i]->idBairro, idBairro) == 0)
        {
            linha = i;
            break;
        }
    }

    if(linha == -1)
    {
        printf("\nElemento não encontrado!\n");
        return;
    }


    NoListaC *ptrLin = listaC->vetorLin[linha];
    NoListaC *antLin = NULL;

    while(ptrLin != NULL && ptrLin->col < coluna)
    {
        antLin = ptrLin;
        ptrLin = ptrLin->proxLin;
    }

    if(ptrLin == NULL || ptrLin->col != coluna)
    {
        printf("\nElemento não encontrado!\n");
        return;
    }


    NoListaC *remover = ptrLin;

    if(ptrLin->col == coluna)
    {
        if(antLin == NULL)
        {
            listaC->vetorLin[linha] = listaC->vetorLin[linha]->proxLin;
        }
        else
        {
            antLin->proxLin = ptrLin->proxLin;
        }
    }

    NoListaC *ptrCol = listaC->vetorCol[coluna];
    NoListaC *antCol = NULL;

    while(ptrCol != NULL && ptrCol->lin < linha)
    {
        antCol = ptrCol;
        ptrCol = ptrCol->proxCol;
    }

    if(ptrCol != NULL && ptrCol->lin == linha)
    {
        if(antCol == NULL)
        {
            listaC->vetorCol[coluna] = listaC->vetorCol[coluna]->proxCol;
        }
        else
        {
            antCol->proxCol = ptrCol->proxCol;
        }
    }

    free(remover);
}

NoListaC *buscarValorListaCruzada(ListaCruzada *listaC, TipoUnidadeServico tipo)
{
    int coluna = tipo;

    NoListaC *atual = listaC->vetorCol[coluna];

    return atual;
}

NoListaC *buscarBairroListaCruzada(ListaCruzada *listaC,
                                   TipoUnidadeServico tipo,
                                   const char *idBairro)
{
    int coluna = tipo;

    NoListaC *atual = listaC->vetorCol[coluna];

    while(atual != NULL && strcmp(atual->idBairro, idBairro) != 0)
    {
        atual = atual->proxCol;
    }

    return atual;
}


void destruirListaCruzada(ListaCruzada *listaC)
{
    for(int i=0; i < MAX_BAIRROS; i++)
    {

        NoListaC *atual = listaC->vetorLin[i];

        while(atual != NULL)
        {
            NoListaC *temp = atual;
            atual = atual->proxLin;
            free(temp);
        }

        listaC->vetorLin[i] = NULL;

    }

    for(int j=0; j < NUM_COLUNAS; j++)
    {
        listaC->vetorCol[j] = NULL;
    }
}
