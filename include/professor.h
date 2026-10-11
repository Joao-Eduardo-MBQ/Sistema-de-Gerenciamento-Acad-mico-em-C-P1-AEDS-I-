#ifndef PROFESSOR_H_INCLUDED
#define PROFESSOR_H_INCLUDED
#include "util.h"

typedef struct {
    int  matricula;
    char nome[TAM_NOME];
    char areaAtuacao[TAM_AREA];
    char email[TAM_EMAIL];
} Professor;

typedef struct {
    Professor dados[MAX_PROFESSOR];
    int       tamanho;
} VetorProfessores;

void iniciarP(VetorProfessores *v);
int  iniciarProfessor(Professor *p, int matricula, const char *nome,
                      const char *area, const char *email);
int  inserirP(VetorProfessores *v, Professor p);
int  removerP(VetorProfessores *v, int matricula);
int  buscarP(const VetorProfessores *v, int matricula);
int  editarProfessor(VetorProfessores *v, int matricula, const char *nome,
                     const char *area, const char *email);
void imprimirProfessor(const Professor *p);
void listarP(const VetorProfessores *v);

#endif