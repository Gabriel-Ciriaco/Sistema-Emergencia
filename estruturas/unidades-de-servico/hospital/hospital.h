#ifndef

#define "HOSPITAL_H"

#define MAX_NOME 30
#define MAX_ID 10

typedef struct{

    char nome[MAX_NOME];
    char id[MAX_ID];
    int capacidadeMaxima;
    int ocorrenciasAtivas;

}Hospital;


#endif
