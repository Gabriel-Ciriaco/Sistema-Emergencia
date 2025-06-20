#include "arvore_abb.h"

#include "../../ocorrencia/ocorrencia.h"

#include<stdlib.h>
#include<string.h>

No *criarNoABB(Ocorrencia ocorrencia)
{
    No *novoNo = (No*)malloc(1*sizeof(No));

    if(novoNo == NULL)
    {
        return NULL;
    }

    novoNo->ocorrencia = ocorrencia;
    novoNo->esq = NULL;
    novoNo->dir = NULL;

    return novoNo;
}

No *inserirValorABB(No *raiz, Ocorrencia ocorrencia)
{
    if(raiz == NULL)
    {
        No *novoNo = criarNoABB(ocorrencia);

        if(novoNo == NULL)
        {
            printf("\nErro ao alocar memória!\n");
            return raiz;
        }

        return novoNo;
    }

    if(strcmp(raiz->ocorrencia.id, ocorrencia.id) == 0)
    {
        return raiz;
    }

    if(strcmp(ocorrencia.id, raiz->ocorrencia.id) < 0)
    {
        raiz->esq = inserirValorABB(raiz->esq, ocorrencia);
    }
    else if(strcmp(ocorrencia.id, raiz->ocorrencia.id) > 0)
    {
        raiz->dir = inserirValorABB(raiz->dir, ocorrencia);
    }

    return raiz;
}

No *buscarValorABB(No *raiz, const char *idOcorrencia)
{
    if(raiz == NULL)
    {
        return NULL;
    }

    if(strcmp(raiz->ocorrencia.id, idOcorrencia) == 0)
    {
        return raiz;
    }

    if(strcmp(idOcorrencia, raiz->ocorrencia.id) < 0)
    {
        return buscarValorABB(raiz->esq, idOcorrencia);
    }
    else
    {
        return buscarValorABB(raiz->dir, idOcorrencia);
    }
}

No *removerValorABB(No *raiz, Ocorrencia ocorrencia)
{
    if(raiz == NULL)
    {
        return NULL;
    }

    if(strcmp(raiz->ocorrencia.id, ocorrencia.id) == 0)
    {
        if(raiz->esq == NULL && raiz->dir == NULL)
        {
            free(raiz);
            return NULL;
        }

        if(raiz->esq != NULL && raiz->dir != NULL)
        {
            No *aux = raiz->esq;

            while(aux->dir != NULL)
            {
                aux = aux->dir;
            }

            Ocorrencia temp = aux->ocorrencia;
            raiz->esq->ocorrencia = temp;

            raiz->esq = removerValorABB(raiz->esq, temp);

            return raiz;
        }
        else
        {
            No *aux;

            if(raiz->esq != NULL)
            {
                aux = raiz->esq;
            }
            else if(raiz->dir != NULL)
            {
                aux = raiz->dir;
            }

            free(raiz);
            return aux;
        }
    }
    else
    {
        if(strcmp(ocorrencia.id, raiz->ocorrencia.id) < 0)
        {
            raiz->esq = removerValorABB(raiz->esq, ocorrencia);
        }
        else
        {
            raiz->dir = removerValorABB(raiz->dir, ocorrencia);
        }

        return raiz;
    }
}

void destruirABB(No *raiz)
{
    if(raiz != NULL)
    {
        destruirABB(raiz->esq);
        destruirABB(raiz->dir);
        free(raiz);
    }
}
