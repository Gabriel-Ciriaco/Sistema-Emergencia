#ifndef POSICAO_H
#define POSICAO_H

typedef struct posicao
{
    float x;
    float y;

} Posicao;

Posicao novaPos(float x, float y);

void addPosX(Posicao * pos, int incrementoX);

void addPosY(Posicao * pos, int incrementoY);

void addPos(Posicao * pos, Posicao * direcao);

void mudarPos(Posicao * pos, float newX, float newY);

float distanciaPos(Posicao * pos1, Posicao * pos2);

void posicaoAleatoria(Posicao * pos);

#endif // POSICAO_H
