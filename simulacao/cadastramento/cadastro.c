#include "cadastro.h"

Bairro cadastrarBairro(TabelaHash * bairros, Bairro * bairro)
{
    ValorHash valor;

    valor.bairro = bairro;

    inserirValor(bairros, bairro->id, valor);
}

Bombeiro cadastrarBombeiro(TabelaHash * bombeiros, Bombeiro * bombeiro)
{
    ValorHash valor;

    valor.unidadeServico->bombeiro = bombeiro;

    inserirValor(bombeiros, bombeiro->id, valor);
}

