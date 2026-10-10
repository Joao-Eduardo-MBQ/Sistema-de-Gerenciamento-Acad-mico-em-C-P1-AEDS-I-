#ifndef PROFESSOR_H_INCLUDED
#define PROFESSOR_H_INCLUDED
#include "util.h"

typedef struct{
    char nomeD[TAM_DISCIPLINA];
    char horario[TAM_HORARIO];
} Aula;

typedef struct {
    int  registro;
    char nomeP[TAM_NOME];
    int  qtdAulas;
    Aula aulas[MAX_AULAS];
} Professor;

typedef struct {
    Professor dados[MAX_PROFESSOR];
    int       tamanho;
} VetorProfessores;

void iniciarP(VetorProfessores *v);
int  inserirP(VetorProfessores *v, Professor p);
int  removerP(VetorProfessores *v, int registro);
int  buscarP(VetorProfessores *v, int registro);
void listarP(VetorProfessores *v);

int  editarProfessor(VetorProfessores *v, int registro, const char *nNome);
int  adicionarAula(VetorProfessores *v, int registro, const char *disciplina, const char *horario);
int  removerAula(VetorProfessores *v, int registro, const char *disciplina);

#endif