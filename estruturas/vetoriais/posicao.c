#include "posicao.h"

#include "../../constantes-sistema/constantes-sistema.h"

#include <stdlib.h>
#include <math.h>


Posicao novaPos(float x, float y)
{
    Posicao novaPosicao;

    novaPosicao.x = x;
    novaPosicao.y = y;

    return novaPosicao;
}

void addPosX(Posicao * pos, int incrementoX)
{
    pos->x += incrementoX;
}

void addPosY(Posicao * pos, int incrementoY)
{
    pos->y += incrementoY;
}

void addPos(Posicao * pos, Posicao * direcao)
{
    pos->x += direcao->x;
    pos->y += direcao->y;
}

void mudarPos(Posicao * pos, float newX, float newY)
{
    pos->x = newX;
    pos->y = newY;
}

float distanciaPos(Posicao * pos1, Posicao * pos2)
{
    return sqrtf(pow(pos2->x - pos1->x, 2) + pow(pos2->y - pos1->y, 2));
}

void posicaoAleatoria(Posicao * pos)
{
    float randX = MIN_RAND_POS + ((float) rand() / (float) RAND_MAX) * (MAX_RAND_POS - MIN_RAND_POS);
    float randY = MIN_RAND_POS + ((float) rand() / (float) RAND_MAX) * (MAX_RAND_POS - MIN_RAND_POS);

    mudarPos(pos, randX, randY);
}
