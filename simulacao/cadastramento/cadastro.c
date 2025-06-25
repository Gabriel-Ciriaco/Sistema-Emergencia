#include "cadastro.h"

#include <stdlib.h>
#include <stdbool.h>

void cadastrarBairro(TabelaHash * bairros, Bairro bairro)
{
    ValorHash valor;

    valor.bairro = bairro;

    inserirValorTabela(bairros, bairro.id, valor);
}

Bairro * resgatarCadastroBairro(TabelaHash * bairros,
                                const char * bairroId)
{
   ValorHash * valor = buscaValorTabela(bairros, bairroId);

   if (!valor) return NULL;

   return &(valor->bairro);
}

void cadastrarCidadao(TabelaHash * cidadaos, Cidadao cidadao)
{
    ValorHash valor;

    valor.cidadao = cidadao;

    inserirValorTabela(cidadaos, cidadao.id, valor);
}

Cidadao * resgatarCadastroCidadao(TabelaHash * cidadaos, const char * cidadaoId)
{
    ValorHash * valor = buscaValorTabela(cidadaos, cidadaoId);

    if (!valor) return NULL;

    return &(valor->cidadao);
}

void cadastrarProfissional(TabelaHash * profissionais, Profissional profissional)
{
    ValorHash valor;

    valor.profissional = profissional;

    inserirValorTabela(profissionais, profissional.cidadao.id, valor);
}

Profissional * resgatarCadastroProfissional(TabelaHash * profissionais, const char * profissionalId)
{
    ValorHash * valor = buscaValorTabela(profissionais, profissionalId);

    if (!valor) return NULL;

    return &(valor->profissional);
}

Profissional * resgatarProfissionalAleatorio(TabelaHash * profissionais, int quantidadeProfissionais)
{
    int profissionalAleatorio = rand() % quantidadeProfissionais;

    int i = 0;

    int profissionaisProcurados = 0;

    bool achouProfissional = false;

    NoHash * no = NULL;

    while(!achouProfissional)
    {
        no = profissionais->tabela[i++];

        if (no)
        {
            profissionaisProcurados++;

            while ( profissionaisProcurados < profissionalAleatorio && no->prox)
            {
                no = no->prox;

                profissionaisProcurados++;
            }

            if (profissionaisProcurados >= profissionalAleatorio) achouProfissional = true;
        }
    }

    return &(no->valor.profissional);
}

void cadastrarBombeiro(TabelaHash * bombeiros, Bombeiro bombeiro)
{
    ValorHash valor;

    valor.unidadeServico.bombeiro = bombeiro;

    inserirValorTabela(bombeiros, bombeiro.id, valor);
}

Bombeiro * resgatarCadastroBombeiro(TabelaHash * bombeiros, const char * bombeiroId)
{
    ValorHash * valor = buscaValorTabela(bombeiros, bombeiroId);

    if (!valor) return NULL;

    return &(valor->unidadeServico.bombeiro);
}

void cadastrarHospital(TabelaHash * hospitais, Hospital hospital)
{
    ValorHash valor;

    valor.unidadeServico.hospital = hospital;

    inserirValorTabela(hospitais, hospital.id, valor);
}

Hospital * resgatarCadastroHospital(TabelaHash * hospitais, const char * hospitalId)
{
    ValorHash * valor = buscaValorTabela(hospitais, hospitalId);

    if (!valor) return NULL;

    return &(valor->unidadeServico.hospital);
}

void cadastrarPolicia(TabelaHash * policias, Policia policia)
{
    ValorHash valor;

    valor.unidadeServico.policia = policia;

    inserirValorTabela(policias, policia.id, valor);
}

Policia * resgatarCadastroPolicia(TabelaHash * policias, const char * policiaId)
{
    ValorHash * valor = buscaValorTabela(policias, policiaId);

    if (!valor) return NULL;

    return &(valor->unidadeServico.policia);
}

void cadastrarSAMU(TabelaHash * samus, SAMU samu)
{
    ValorHash valor;

    valor.unidadeServico.samu = samu;

    inserirValorTabela(samus, samu.id, valor);
}

SAMU * resgatarCadastroSAMU(TabelaHash * samus, const char * samuId)
{
    ValorHash * valor = buscaValorTabela(samus, samuId);

    if (!valor) return NULL;

    return &(valor->unidadeServico.samu);
}
