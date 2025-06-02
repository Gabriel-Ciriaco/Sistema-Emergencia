#include "controle-de-tempo.h"

#include <time.h>


void formatarTempo(char * hora, struct tm * horaTM)
{
    strftime(hora, FORMATO_TEMPO, "%H:%M:%S", horaTM);
}

void calcularTempoAtual(char * hora)
{
    time_t t = time(NULL);

    struct tm horaAtual = *localtime(&t);

    formatarTempo(hora, &horaAtual);
}
