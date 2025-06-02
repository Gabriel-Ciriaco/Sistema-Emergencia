#include "simulacao/simulacao.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "./simulacao/geradores/geradores.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");

    Simulador simulador = criarSimulador();

    alterarTempoSimulacao(&simulador, 2);

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
