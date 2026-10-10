#ifndef TURMA_H_INCLUDED
#define TURMA_H_INCLUDED
#include "util.h"
#include "aluno.h"
#include "professor.h"
#include "disciplina.h"

typedef struct {
    int  nTurma;
    char sala[TAM_SALA];
    char materia[TAM_DISCIPLINA];
    int  registroProf;                 /* -1 = sem professor */
    int  matriculas[MAX_ALUNOS_TURMA];
    int  qtdAlunos;
} Turma;

typedef struct {
    Turma dados[MAX_TURMAS];
    int   tamanho;
} VetorTurmas;

void iniciarVetorTurmas(VetorTurmas *vt);
void iniciarTurma(Turma *t, int nTurma, const char *sala, const char *materia);
int  buscarturma(VetorTurmas *vt, int nTurma);
int  inserirTurma(VetorTurmas *vt, Turma t);
int  removerTurma(VetorTurmas *vt, int nTurma);
int  adicionarAlunoTurma(VetorTurmas *vt, int nTurma, int matricula);
int  removerAlunoTurma(VetorTurmas *vt, int nTurma, int matricula);
void imprimirTurma(const Turma *t, VetorProfessores *vp);
void listarTurmas(VetorTurmas *vt, VetorProfessores *vp);
int  designarProfessorTurma(VetorTurmas *vt, int nTurma, int registro);

#endif