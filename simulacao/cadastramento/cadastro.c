#include "cadastro.h"

Bairro cadastrarBairro(TabelaHash * bairros, Bairro * bairro)
{
    ValorHash valor;

    valor.bairro = bairro;

    inserirValorTabela(bairros, bairro->id, valor);
}

Bombeiro cadastrarBombeiro(TabelaHash * bombeiros, Bombeiro * bombeiro)
{
    ValorHash valor;

    valor.unidadeServico->bombeiro = bombeiro;

    inserirValorTabela(bombeiros, bombeiro->id, valor);
}

Hospital cadastrarHospital(TabelaHash * hospitais, Hospital * hospital)
{
    ValorHash valor;

    valor.unidadeServico->hospital = hospital;

    inserirValorTabela(hospitais, hospital->id, valor);
}

Policia cadastrarPolicia(TabelaHash * policias, Policia * policia);
{
    ValorHash valor;

    valor.unidadeSevico->policia = policia;

    inserirValorTabela(policias, policia->id, valor);
}

SAMU cadastrarSAMU(TabelaHash * samus, SAMU * samu);
{
    ValorHash valor;

    valor.unidadeServico->samu = samu;

    inserirValorTabela(samus, samu->id, valor);
}
