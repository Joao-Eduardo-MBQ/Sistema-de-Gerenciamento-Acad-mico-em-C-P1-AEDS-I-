#ifndef DISCIPLINA_H_INCLUDED
#define DISCIPLINA_H_INCLUDED
#include "util.h"

typedef struct {
    int  codigo;
    char nome[TAM_DISCIPLINA];
    int  cargaHoraria;
    char periodo[TAM_PERIODO];
    int  vagas;
    int  prerequisitos[MAX_PREREQ];     /* codigos das disciplinas exigidas */
    int  qtdPrereq;
} Disciplina;

typedef struct {
    Disciplina dados[MAX_DISCIPLINAS];
    int        tamanho;
} VetorDisciplinas;

void iniciarVetorDisciplinas(VetorDisciplinas *vd);
int  iniciarDisciplina(Disciplina *d, int codigo, const char *nome, int cargaHoraria,
                       const char *periodo, int vagas);
int  buscarDisciplina(const VetorDisciplinas *vd, int codigo);
int  inserirDisciplina(VetorDisciplinas *vd, Disciplina d);
int  removerDisciplina(VetorDisciplinas *vd, int codigo);
int  editarDisciplina(VetorDisciplinas *vd, int codigo, const char *nome, int cargaHoraria,
                      const char *periodo, int vagas);
void imprimirDisciplina(const Disciplina *d);
void listarDisciplinas(const VetorDisciplinas *vd);

/* pre-requisitos */
int  adicionarPrerequisito(VetorDisciplinas *vd, int codigo, int codPrereq);
int  removerPrerequisito(VetorDisciplinas *vd, int codigo, int codPrereq);
int  disciplinaEhPrerequisito(const VetorDisciplinas *vd, int codigo);
void listarPrerequisitos(const VetorDisciplinas *vd, int codigo);

#endif