#include <stdio.h>
#include <string.h>
#include "../include/professor.h"

void iniciarP(VetorProfessores *v){
    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return;
    }
    v->tamanho = 0;
}

int iniciarProfessor(Professor *p, int matricula, const char *nome, const char *area, const char *email){
    if(p == NULL || nome == NULL || area == NULL || email == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    if(matricula <= 0){
        printf("Matricula invalida.\n");
        return 0;
    }


    memset(p, 0, sizeof(*p));
    p->matricula = matricula;
    strncpy(p->nome, nome, sizeof(p->nome) - 1);
    p->nome[sizeof(p->nome) - 1] = '\0';
    strncpy(p->areaAtuacao, area, sizeof(p->areaAtuacao) - 1);
    p->areaAtuacao[sizeof(p->areaAtuacao) - 1] = '\0';
    strncpy(p->email, email, sizeof(p->email) - 1);
    p->email[sizeof(p->email) - 1] = '\0';
    return 1;
}

int inserirP(VetorProfessores *v, Professor p){
    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    if(v->tamanho >= MAX_PROFESSOR){
        printf("Vetor de professores cheio.\n");
        return 0;
    }

    if(buscarP(v, p.matricula) != -1){
        printf("Professor ja cadastrado.\n");
        return 0;
    }

    v->dados[v->tamanho] = p;
    v->tamanho++;
    return 1;
}

int removerP(VetorProfessores *v, int matricula){
    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    int i = buscarP(v, matricula);
    if(i == -1){
        printf("Professor nao encontrado.\n");
        return 0;
    }

    for(int j = i; j < v->tamanho - 1; j++){
        v->dados[j] = v->dados[j + 1];
    }
    v->tamanho--;
    return 1;
}

int buscarP(const VetorProfessores *v, int matricula){
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

int editarProfessor(VetorProfessores *v, int matricula, const char *nome, const char *area, const char *email){
    if(v == NULL || nome == NULL || area == NULL || email == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    int i = buscarP(v, matricula);
    if(i == -1){
        printf("Professor nao encontrado.\n");
        return 0;
    }


    Professor *p = &v->dados[i];
    strncpy(p->nome, nome, sizeof(p->nome) - 1);
    p->nome[sizeof(p->nome) - 1] = '\0';
    strncpy(p->areaAtuacao, area, sizeof(p->areaAtuacao) - 1);
    p->areaAtuacao[sizeof(p->areaAtuacao) - 1] = '\0';
    strncpy(p->email, email, sizeof(p->email) - 1);
    p->email[sizeof(p->email) - 1] = '\0';
    return 1;
}

void imprimirProfessor(const Professor *p){
    printf("Matricula: %d | Nome: %s | Area: %s | E-mail: %s\n",
           p->matricula, p->nome, p->areaAtuacao, p->email);
}

void listarP(const VetorProfessores *v){
    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return; 
    }

    if(v->tamanho == 0){
        printf("Nao existem professores cadastrados.\n");
        return;
    }

    for(int i = 0; i < v->tamanho; i++){
        imprimirProfessor(&v->dados[i]);
    }
}