#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include "util.h"
#include "aluno.h"

typedef struct {
    int dados[MAX_FILA];
    int inicio;
    int tamanho;
} FilaAtendimento;

void iniciarFila(FilaAtendimento *f);
int  filaVazia(const FilaAtendimento *f);
int  filaCheia(const FilaAtendimento *f);
int  filaContem(const FilaAtendimento *f, int matricula);
int  entrarNaFila(FilaAtendimento *f, const VetorAlunos *va, int matricula);
int  atenderProximo(FilaAtendimento *f, const VetorAlunos *va);
void proximoDaFila(const FilaAtendimento *f, const VetorAlunos *va);
void listarFila(const FilaAtendimento *f, const VetorAlunos *va);

#endif