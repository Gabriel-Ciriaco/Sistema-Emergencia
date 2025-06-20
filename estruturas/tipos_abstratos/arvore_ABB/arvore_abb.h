#ifndef ARVORE_ABB_H_INCLUDED
#define ARVORE_ABB_H_INCLUDED

#include "../../ocorrencia/ocorrencia.h"

typedef struct no
{
    Ocorrencia ocorrencia;
    struct no *esq;
    struct no *dir;
}No;

No *criarNoABB(Ocorrencia ocorrencia);

No *inserirValorABB(No *raiz, Ocorrencia ocorrencia);

No *buscarValorABB(No *raiz, const char *idOcorrencia);

No *removerValorABB(No *raiz, Ocorrencia ocorrencia);

void destruirABB(No *raiz);

#endif // ARVORE_ABB_H_INCLUDED
