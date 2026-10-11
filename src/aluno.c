#include <stdio.h>
#include <string.h>
#include "../include/aluno.h"

void iniciarA(VetorAlunos *v){
    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return;
    }
    v->tamanho = 0;
}

int iniciarAluno(Aluno *a, int matricula, const char *nome, const char *curso,
                 const char *periodo, const char *email){
    if(a == NULL || nome == NULL || curso == NULL || periodo == NULL || email == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    if(matricula <= 0){
        printf("Matricula invalida.\n");
        return 0;
    }


    memset(a, 0, sizeof(*a));
    a->matricula = matricula;
    strncpy(a->nome, nome, sizeof(a->nome) - 1);
    a->nome[sizeof(a->nome) - 1] = '\0';
    strncpy(a->curso, curso, sizeof(a->curso) - 1);
    a->curso[sizeof(a->curso) - 1] = '\0';
    strncpy(a->periodo, periodo, sizeof(a->periodo) - 1);
    a->periodo[sizeof(a->periodo) - 1] = '\0';
    strncpy(a->email, email, sizeof(a->email) - 1);
    a->email[sizeof(a->email) - 1] = '\0';
    return 1;
}

int inserirA(VetorAlunos *v, Aluno a){
    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    if(v->tamanho >= MAX_ALUNO){
        printf("Vetor de alunos cheio.\n");
        return 0;
    }

    if(buscarA(v, a.matricula) != -1){
        printf("Aluno ja cadastrado.\n");
        return 0;
    }

    v->dados[v->tamanho] = a;
    v->tamanho++;
    return 1;
}

int removerA(VetorAlunos *v, int matricula){
    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    int i = buscarA(v, matricula);
    if(i == -1){
        printf("Aluno nao encontrado.\n");
        return 0;
    }

    for(int j = i; j < v->tamanho - 1; j++){
        v->dados[j] = v->dados[j + 1];
    }
    v->tamanho--;
    return 1;
}

int buscarA(const VetorAlunos *v, int matricula){
    if(v == NULL){
        return -1;
    }

    for(int i = 0; i < v->tamanho; i++){
        if(v->dados[i].matricula == matricula){
            return i;
        }
    }
    return -1;
}

int editarAluno(VetorAlunos *v, int matricula, const char *nome, const char *curso,
                const char *periodo, const char *email){
    if(v == NULL || nome == NULL || curso == NULL || periodo == NULL || email == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    int i = buscarA(v, matricula);
    if(i == -1){
        printf("Aluno nao encontrado.\n");
        return 0;
    }


    Aluno *a = &v->dados[i];
    strncpy(a->nome, nome, sizeof(a->nome) - 1);
    a->nome[sizeof(a->nome) - 1] = '\0';
    strncpy(a->curso, curso, sizeof(a->curso) - 1);
    a->curso[sizeof(a->curso) - 1] = '\0';
    strncpy(a->periodo, periodo, sizeof(a->periodo) - 1);
    a->periodo[sizeof(a->periodo) - 1] = '\0';
    strncpy(a->email, email, sizeof(a->email) - 1);
    a->email[sizeof(a->email) - 1] = '\0';
    return 1;
}

void imprimirAluno(const Aluno *a){
    printf("Matricula: %d | Nome: %s | Curso: %s | Periodo: %s | E-mail: %s\n",
           a->matricula, a->nome, a->curso, a->periodo, a->email);
}

void listarA(const VetorAlunos *v){
    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return;
    }

    if(v->tamanho == 0){
        printf("Nao existem alunos cadastrados.\n");
        return;
    }

    for(int i = 0; i < v->tamanho; i++){
        imprimirAluno(&v->dados[i]);
    }
}