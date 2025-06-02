#include "simulacao/simulacao.h"
#include "./simulacao/geradores/geradores.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


int main()
{
    setlocale(LC_ALL, "Portuguese");

    Simulador simulador = criarSimulador();

    alterarTempoMaximoSimulacao(&simulador, 10);

    printf("\n** Simulação Iniciada **\n");

    if (rodarSimulacao(&simulador))
    {
        printf("\n** Simulação finalizada com sucesso. **\n");
    }
    else
    {
        printf("\n** Houve algum problema ao finalizar o simulador. ** \n");
    }


    return 0;
}
