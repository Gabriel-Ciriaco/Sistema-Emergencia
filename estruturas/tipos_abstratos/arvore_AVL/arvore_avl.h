#ifndef ARVORE_AVL_H_INCLUDED
#define ARVORE_AVL_H_INCLUDED

#include "../../ocorrencia/ocorrencia.h"

typedef struct noAvl
{
    Ocorrencia ocorrencia;
    struct noAvl *esq;
    struct noAvl *dir;
    int altura;

}NoAvl;

NoAvl * criarArvoreAvl();

NoAvl *criarNoAVL(Ocorrencia ocorrencia);

int alturaNoAvl(NoAvl *noAvl);

int maxValor(int a, int b);

int fatorBalanceamento(NoAvl *noAvl);

NoAvl *rotacaoEsq(NoAvl *raiz);

NoAvl *rotacaoDir(NoAvl *raiz);

NoAvl *rotacaoDirEsq(NoAvl *raiz);

NoAvl *rotacaoEsqDir(NoAvl *raiz);

NoAvl *balanceamentoAVL(NoAvl *raiz);

NoAvl *inserirValorAVL(NoAvl *raiz, Ocorrencia ocorrencia);

NoAvl *buscarValorAVL(NoAvl *raiz, char const *idOcorrencia);

NoAvl *removerValorAVL(NoAvl *raiz, Ocorrencia ocorrencia);

void destruirAVL(NoAvl *raiz);

#endif // ARVORE_AVL_H_INCLUDED
