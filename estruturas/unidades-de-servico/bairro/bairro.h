#ifndef

#define "BAIRRO_H"

#define MAX_ID 10
#define MAX_NOME 30

typedef struct{

    char id[MAX_ID];
    char nome[MAX_NOME];

    typedef union{

        Hospital hospital;
        SAMU samu;
        Bombeiro bombeiro;
        Policia policia;

    }unidadesServico;

}Bairro;

#endif
