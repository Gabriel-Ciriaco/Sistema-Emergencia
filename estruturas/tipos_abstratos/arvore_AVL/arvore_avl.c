#include "arvore_avl.h"

#include "../../ocorrencia/ocorrencia.h"

#include<stdlib.h>
#include<string.h>


NoAvl * criarArvoreAvl()
{
    NoAvl * raiz = NULL;

    return raiz;
}

NoAvl *criarNoAVL(Ocorrencia ocorrencia)
{
    NoAvl *novoNo = (NoAvl*)malloc(1*sizeof(NoAvl));

    if(novoNo == NULL)
    {
        return NULL;
    }

    novoNo->ocorrencia = ocorrencia;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->altura = 0;

    return novoNo;
}

int alturaNo(NoAvl *noAvl)
{
    if(noAvl == NULL)
    {
        return -1;
    }

    return noAvl->altura;
}

int maxValor(int a, int b)
{
    if(a > b)
    {
        return a;
    }

    return b;
}

int fatorBalanceamento(NoAvl *noAvl)
{
    if(noAvl == NULL)
    {
        return 0;
    }
    else
    {
        return (alturaNo(noAvl->esq) - alturaNo(noAvl->dir));
    }
}

NoAvl *rotacaoEsq(NoAvl *raiz)
{
    NoAvl *y = raiz->dir;
    NoAvl *f = y->esq;

    y->esq = raiz;
    raiz->dir = f;

    raiz->altura = maxValor(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
    y->altura = maxValor(alturaNo(y->esq), alturaNo(y->dir)) + 1;

    return y;
}

NoAvl *rotacaoDir(NoAvl *raiz)
{
    NoAvl *y = raiz->esq;
    NoAvl *f = y->dir;

    y->dir = raiz;
    raiz->esq = f;

    raiz->altura = maxValor(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
    y->altura = maxValor(alturaNo(y->esq), alturaNo(y->dir)) + 1;

    return y;
}

NoAvl *rotacaoDirEsq(NoAvl *raiz)
{
    raiz->dir = rotacaoDir(raiz->dir);

    raiz = rotacaoEsq(raiz);

    return raiz;
}

NoAvl *rotacaoEsqDir(NoAvl *raiz)
{
    raiz->esq = rotacaoEsq(raiz->esq);

    raiz = rotacaoDir(raiz);

    return raiz;
}

NoAvl *balanceamentoAVL(NoAvl *raiz)
{
    if(raiz == NULL)
    {
        return NULL;
    }

    int fb = fatorBalanceamento(raiz);

    if(fb < -1 && fatorBalanceamento(raiz->dir) <= 0)
    {
        raiz = rotacaoEsq(raiz);
    }
    else if(fb > 1 && fatorBalanceamento(raiz->esq) >= 0)
    {
        raiz = rotacaoDir(raiz);
    }
    else if(fb < -1 && fatorBalanceamento(raiz->dir) > 0)
    {
        raiz = rotacaoDirEsq(raiz);
    }
    else if(fb > 1 && fatorBalanceamento(raiz->esq) < 0)
    {
        raiz = rotacaoEsqDir(raiz);
    }

    return raiz;
}

NoAvl *inserirValorAVL(NoAvl *raiz, Ocorrencia ocorrencia)
{
    if(raiz == NULL)
    {
        NoAvl *novoNo = criarNoAVL(ocorrencia);

        if(novoNo == NULL)
        {
            return NULL;
        }

        return novoNo;
    }
    else
    {
        if(ocorrencia.gravidade < raiz->ocorrencia.gravidade)
        {
            raiz->esq = inserirValorAVL(raiz->esq, ocorrencia);
        }
        else if(ocorrencia.gravidade >= raiz->ocorrencia.gravidade)
        {
            raiz->dir = inserirValorAVL(raiz->dir, ocorrencia);
        }

    }

    raiz->altura = maxValor(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;

    raiz = balanceamentoAVL(raiz);

    return raiz;
}

NoAvl *buscarValorAVL(NoAvl *raiz, char const *idOcorrencia)
{
    if(raiz == NULL)
    {
        return NULL;
    }

    if(strcmp(idOcorrencia, raiz->ocorrencia.id) == 0)
    {
        return raiz;
    }

    if(strcmp(idOcorrencia, raiz->ocorrencia.id) < 0)
    {
        return buscarValorAVL(raiz->esq, idOcorrencia);
    }
    else
    {
        return buscarValorAVL(raiz->dir, idOcorrencia);
    }
}

NoAvl *removerValorAVL(NoAvl *raiz, Ocorrencia ocorrencia)
{
    if(raiz == NULL)
    {
        return NULL;
    }
    else
    {
        if(strcmp(ocorrencia.id, raiz->ocorrencia.id) == 0)
        {
            if(raiz->esq == NULL && raiz->dir == NULL)
            {
                free(raiz);
                return NULL;
            }

            if(raiz->esq != NULL && raiz->dir != NULL)
            {
                NoAvl *aux = raiz->esq;

                while(aux->dir != NULL)
                {
                    aux = aux->dir;
                }

                Ocorrencia temp = aux->ocorrencia;

                raiz->esq->ocorrencia = temp;

                raiz->esq = removerValorAVL(raiz->esq, temp);

                return raiz;
            }
            else
            {
                NoAvl *aux;
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
                raiz->esq = removerValorAVL(raiz->esq, ocorrencia);
            }
            else
            {
                raiz->dir = removerValorAVL(raiz->dir, ocorrencia);
            }
        }

        raiz->altura = maxValor(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;

        raiz = balanceamentoAVL(raiz);

        return raiz;
    }
}

void destruirAVL(NoAvl *raiz)
{
    if(raiz != NULL)
    {
        destruirAVL(raiz->esq);
        destruirAVL(raiz->dir);
        free(raiz);
    }
}
