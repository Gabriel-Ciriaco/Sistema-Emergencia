#ifndef ArvoreABB_ABB_H_INCLUDED
#define ArvoreABB_ABB_H_INCLUDED

#include "../../ocorrencia/ocorrencia.h"

typedef struct ArvoreABB
{
    Ocorrencia ocorrencia;
    struct ArvoreABB *esq;
    struct ArvoreABB *dir;
}ArvoreABB;

ArvoreABB *criarABB();

ArvoreABB *criarArvoreABBABB(Ocorrencia ocorrencia);

ArvoreABB *inserirValorABB(ArvoreABB *raiz, Ocorrencia ocorrencia);

ArvoreABB *buscarValorABB(ArvoreABB *raiz, const char *idOcorrencia);

ArvoreABB *removerValorABB(ArvoreABB *raiz, Ocorrencia ocorrencia);

void destruirABB(ArvoreABB *raiz);

#endif // ArvoreABB_ABB_H_INCLUDED
