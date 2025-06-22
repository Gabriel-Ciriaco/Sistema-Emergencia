#include "texto_aleatorio.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int quantidadeTextosDisponiveis(char * TEXTOS_PATH)
{
    if (TEXTOS_PATH == NULL) return -1;

    FILE * lista_textos = fopen(TEXTOS_PATH, "r");

    if (!lista_textos) return -1;


    int quantidadeTextos = 0;

    char linha[MAX_TEXTO];

    while(fgets(linha, sizeof(linha), lista_textos))
    {
        // Procura e remove a quebra de linha.
        linha[strcspn(linha, "\r\n")] = '\0';

        int temLetra = false;

        // A linha tem que ter pelo menos uma letra.
        for (int j = 0; linha[j] != '\0'; j++)
        {
            if (isalpha(linha[j]))
            {
                temLetra = true;
                break;
            }
        }

        if (temLetra) quantidadeTextos++;
    }

    fclose(lista_textos);

    return quantidadeTextos;
}

void textoAleatorio(char * texto, char * TEXTOS_PATH)
{
    FILE * lista_textos = fopen(TEXTOS_PATH, "r");

    if (!lista_textos)
    {
        printf("\n** Falha ao abrir o arquivo: %s", TEXTOS_PATH);

        perror(" *");

        strcpy(texto, ""); // Texto vazio, indicando erro.
    }
    else
    {
        int quantidadeTextos = quantidadeTextosDisponiveis(TEXTOS_PATH);

        char textos_possiveis[quantidadeTextos][MAX_TEXTO];

        char linha[MAX_TEXTO];

        int i = 0;

        while(fgets(linha, sizeof(linha), lista_textos))
        {
            // Procura e remove a quebra de linha.
            linha[strcspn(linha, "\r\n")] = '\0';

            int temLetra = false;

            // A linha tem que ter pelo menos uma letra.
            for (int j = 0; linha[j] != '\0'; j++)
            {
                if (isalpha(linha[j]))
                {
                    temLetra = true;
                    break;
                }
            }

            if (temLetra)
            {
                strncpy(textos_possiveis[i], linha, MAX_TEXTO);

                textos_possiveis[i][MAX_TEXTO - 1] = '\0'; // Garantir a finalização da string.

                i++;
            }


        }

        strcpy(texto, textos_possiveis[rand() % quantidadeTextos]);
    }

    fclose(lista_textos);

}
