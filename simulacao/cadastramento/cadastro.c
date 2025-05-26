#include "cadastro.h"

Bairro cadastrarBairro(TabelaHash * bairros, Bairro * bairro)
{
    ValorHash valor;

    valor.bairro = bairro;

    inserirValorTabela(bairros, bairro->id, valor);
}

Cidadao cadastrarCidadao(TabelaHash * cidadaos, Cidadao * cidadao)
{
    Cidadao novoCidadao;

    //TO-DO: Terminar a implementação do novo cidadão.

    return novoCidadao;
}

Bombeiro cadastrarBombeiro(TabelaHash * bombeiros, Bombeiro bombeiro)
{
    ValorHash valor;

    valor.unidadeServico->bombeiro = bombeiro;

    inserirValorTabela(bombeiros, bombeiro.id, valor);
}

Hospital cadastrarHospital(TabelaHash * hospitais, Hospital hospital)
{
    ValorHash valor;

    valor.unidadeServico->hospital = hospital;

    inserirValorTabela(hospitais, hospital.id, valor);
}

Policia cadastrarPolicia(TabelaHash * policias, Policia policia)
{
    ValorHash valor;

    valor.unidadeServico->policia = policia;

    inserirValorTabela(policias, policia.id, valor);
}

SAMU cadastrarSAMU(TabelaHash * samus, SAMU samu)
{
    ValorHash valor;

    valor.unidadeServico->samu = samu;

    inserirValorTabela(samus, samu.id, valor);
}
