#include "atendimento.h"

#include "../../estruturas/vetoriais/posicao.h"

#include "../cadastramento/cadastro.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>


Bairro * procurarBairroProximo(ListaCruzada * bairrosUnidades,
                               TabelaHash * bairros,
                               Ocorrencia ocorrencia)
{
    TipoUnidadeServico tipoUni;

    switch (ocorrencia.tipo)
    {
        case OCORRENCIA_BOMBEIRO:
            tipoUni = TUS_BOMBEIRO;
            break;

        case OCORRENCIA_HOSPITAL:
            tipoUni = TUS_HOSPITAL;
            break;

        case OCORRENCIA_POLICIA:
            tipoUni = TUS_POLICIA;
            break;

        default:
            return NULL;
    }

    // Retorna o bairro com a unidade de serviço desejada.
    NoListaC * noLista = buscarValorListaCruzada(bairrosUnidades, tipoUni);

    if (!noLista) return NULL;

    Bairro * bairroAtual = NULL;
    Bairro * bairroMaisProximo = NULL;

    float menorDistancia = FLT_MAX; // Iniciamos com o maior float possível.

    float distanciaAtual = menorDistancia;

    while (noLista)
    {
        bairroAtual = resgatarCadastroBairro(bairros, noLista->idBairro);

        if (bairroAtual)
        {
            distanciaAtual = distanciaPos(ocorrencia.vitima->pos, bairroAtual->pos);


            if (distanciaAtual < menorDistancia)
            {
                menorDistancia = distanciaAtual;

                bairroMaisProximo = bairroAtual;
            }
        }

        noLista = noLista->proxCol; // Verifica o próximo bairro.
    }

    return bairroMaisProximo;
}

void inserirFilaGravidade(FilaPrioridade * filaP, Ocorrencia ocorrencia)
{
    ValorFilaPrioridade valor;

    valor.ocorrencia = ocorrencia;

    if (ocorrencia.gravidade == GRAVIDADE_MEDIA ||
        ocorrencia.gravidade == GRAVIDADE_ALTA)
    {
        inserirValorFilaPInicio(filaP, valor);
    }
    else
    {
        inserirValorFilaPFim(filaP, valor);
    }
}

Ocorrencia removerOcorrenciaFila(FilaPrioridade * filaP)
{
    ValorFilaPrioridade valor = removerValorFilaP(filaP);

    return valor.ocorrencia;
}

void tratarFilaOcorrencia(FilaPrioridade * filaP,
                          const char * tempoSimulacao,
                          const char * nomeFila)
{
    if (!estaVaziaFilaP(filaP))
    {
        ValorFilaPrioridade valor = removerValorFilaP(filaP);

        printf("\n[%s]: Ocorrência retirada da fila de %s: %s\n",
                tempoSimulacao, nomeFila, valor.ocorrencia.id);

    }
}
