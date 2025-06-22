#ifndef CONTROLE_DE_TEMPO_H
#define CONTROLE_DE_TEMPO_H

#include <time.h>

#define FORMATO_TEMPO 9


// Armazena o tempo da struct tm na string.
void formatarTempo(char * hora, struct tm * horaTM);

void calcularTempoAtual(char * hora);

#endif // CONTROLE_DE_TEMPO_H
