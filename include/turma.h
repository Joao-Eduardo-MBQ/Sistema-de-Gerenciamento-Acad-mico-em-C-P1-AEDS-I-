#ifndef TURMA_H_INCLUDED
#define TURMA_H_INCLUDED
#include "util.h"
#include "disciplina.h"
#include "professor.h"

typedef struct {
    int  codigo;
    int  codDisciplina;
    int  matProfessor;
    char horario[TAM_HORARIO];
    char sala[TAM_SALA];
    int  vagas;
} Turma;

typedef struct {
    Turma dados[MAX_TURMAS];
    int   tamanho;
} VetorTurmas;

void iniciarVetorTurmas(VetorTurmas *vt);
int  buscarTurma(const VetorTurmas *vt, int codigo);
int  cadastrarTurma(VetorTurmas *vt, const VetorDisciplinas *vd, const VetorProfessores *vp, int codigo, int codDisciplina, int matProfessor, const char *horario, const char *sala, int vagas);
int  removerTurma(VetorTurmas *vt, int codigo);
void imprimirTurma(const Turma *t, const VetorDisciplinas *vd, const VetorProfessores *vp, int ocupadas);

int  professorTemTurma(const VetorTurmas *vt, int matProfessor);
int  disciplinaTemTurma(const VetorTurmas *vt, int codDisciplina);

#endif