#ifndef ALUNO_H_INCLUDED
#define ALUNO_H_INCLUDED
#include "util.h"

typedef struct {
    int  matricula;
    char nome[TAM_NOME];
    char curso[TAM_CURSO];
    char periodo[TAM_PERIODO];
    char email[TAM_EMAIL];
} Aluno;

typedef struct {
    Aluno dados[MAX_ALUNO];
    int   tamanho;
} VetorAlunos;

void iniciarA(VetorAlunos *v);
int  iniciarAluno(Aluno *a, int matricula, const char *nome, const char *curso,
                  const char *periodo, const char *email);
int  inserirA(VetorAlunos *v, Aluno a);
int  removerA(VetorAlunos *v, int matricula);
int  buscarA(const VetorAlunos *v, int matricula);
int  editarAluno(VetorAlunos *v, int matricula, const char *nome, const char *curso,
                 const char *periodo, const char *email);
void imprimirAluno(const Aluno *a);
void listarA(const VetorAlunos *v);

#endif