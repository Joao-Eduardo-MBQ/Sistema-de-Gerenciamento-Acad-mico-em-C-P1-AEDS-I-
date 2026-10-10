#ifndef ALUNO_H_INCLUDED
#define ALUNO_H_INCLUDED
#include "util.h"

typedef struct {
    char  nomeD[TAM_DISCIPLINA];
    float notas[MAX_PROVAS];
    int   qtdN;
} Disciplina;

typedef struct {
    int        matricula;
    char       nomeA[TAM_NOME];
    int        idadeA;
    char       curso[TAM_CURSO];
    int        qtdD;
    Disciplina ds[MAX_DISCIPLINAS];
} Aluno;

typedef struct {
    Aluno dados[MAX_ALUNO];
    int   tamanho;
} VetorAlunos;

void  iniciarA(VetorAlunos *v);
int   inserirA(VetorAlunos *v, Aluno a);
int   removerA(VetorAlunos *v, int matricula);
int   buscarA(VetorAlunos *v, int matricula);
void  listarA(VetorAlunos *v);

int   editarAluno(VetorAlunos *v, int matricula, const char *nNome, int nIdade, const char *nCurso);
int   adicionarDisciplina(VetorAlunos *v, int matricula, const char *nomeDisc);
int   removerDisciplina(VetorAlunos *v, int matricula, const char *nomeDisc);
int   lancarNota(VetorAlunos *v, int matricula, const char *nomeDisc, int prova, float nota);

#endif