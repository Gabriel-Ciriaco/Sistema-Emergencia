#ifndef ARVORE_AVL_H_INCLUDED
#define ARVORE_AVL_H_INCLUDED

#include "../../ocorrencia/ocorrencia.h"

typedef struct no
{
    Ocorrencia ocorrencia;
    struct no *esq;
    struct no *dir;
    int altura;

}No;

No *criarNoAVL(Ocorrencia ocorrencia);

int alturaNo(No *no);

int maxValor(int a, int b);

int fatorBalanceamento(No *no);

No *rotacaoEsq(No *raiz);

No *rotacaoDir(No *raiz);

No *rotacaoDirEsq(No *raiz);

No *rotacaoEsqDir(No *raiz);

No *balanceamentoAVL(No *raiz);

No *inserirValorAVL(No *raiz, Ocorrencia ocorrencia);

No *buscarValorAVL(No *raiz, char const *idOcorrencia);

No *removerValorAVL(No *raiz, Ocorrencia ocorrencia);

void destruirAVL(No *raiz);

#endif // ARVORE_AVL_H_INCLUDED
