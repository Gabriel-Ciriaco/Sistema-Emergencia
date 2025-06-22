#include "simulacao/simulacao.h"
#include "./simulacao/geradores/geradores.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


int main()
{
    setlocale(LC_ALL, "Portuguese");

    Simulador simulador = criarSimulador();

    alterarTempoMaximoSimulacao(&simulador, 30);

    alterarQuantidadeOcorrenciasCiclo(&simulador, 5);

    printf("\n** Simula��o Iniciada **\n");

    if (rodarSimulacao(&simulador))
    {
        printf("\n** Simula��o finalizada com sucesso. **\n");
    }
    else
    {
        printf("\n** Houve algum problema ao finalizar o simulador. ** \n");
    }


    return 0;
}
