#ifndef MATRICULA_H_INCLUDED
#define MATRICULA_H_INCLUDED
#include "util.h"
#include "aluno.h"
#include "disciplina.h"
#include "turma.h"

typedef enum {
    SIT_CURSANDO,
    SIT_APROVADO,
    SIT_REPROVADO,
    SIT_CANCELADO
} Situacao;

typedef struct {
    int      matAluno;
    int      codTurma;
    char     semestre[TAM_SEMESTRE];
    float    nota;
    float    frequencia;        
    int      notaLancada;
    int      freqLancada;
    Situacao situacao;
} Matricula;

typedef struct {
    Matricula dados[MAX_MATRICULAS];
    int       tamanho;
} VetorMatriculas;

void iniciarVetorMatriculas(VetorMatriculas *vm);
const char *nomeSituacao(Situacao s);
int buscarMatricula(const VetorMatriculas *vm, int matAluno, int codTurma);

int  matricularAluno(VetorMatriculas *vm, const VetorAlunos *va, const VetorTurmas *vt, const VetorDisciplinas *vd, int matAluno, int codTurma, const char *semestre);
int  cancelarMatricula(VetorMatriculas *vm, int matAluno, int codTurma);
int  registrarNota(VetorMatriculas *vm, int matAluno, int codTurma, float nota);
int  registrarFrequencia(VetorMatriculas *vm, int matAluno, int codTurma, float freq);

int  contarAlunosTurma(const VetorMatriculas *vm, int codTurma);
int  alunoTemPendencias(const VetorMatriculas *vm, int matAluno);
void removerMatriculasDoAluno(VetorMatriculas *vm, int matAluno);

void consultarSituacaoAcademica(const VetorMatriculas *vm, const VetorAlunos *va, int matAluno);
void listarAlunosTurma(const VetorMatriculas *vm, const VetorAlunos *va, const VetorTurmas *vt, int codTurma);
void listarDisciplinasAluno(const VetorMatriculas *vm, const VetorAlunos *va, const VetorTurmas *vt, const VetorDisciplinas *vd, int matAluno);
void historicoAcademico(const VetorMatriculas *vm, const VetorAlunos *va, const VetorTurmas *vt, const VetorDisciplinas *vd, int matAluno);

#endif