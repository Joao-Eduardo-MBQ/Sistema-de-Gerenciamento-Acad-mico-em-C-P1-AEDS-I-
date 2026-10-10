#include "professor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void iniciarP(VetorProfessores *v){ // O(1)

    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return;
    }

    v->tamanho = 0;
};

int inserirP(VetorProfessores *v, Professor p){ // O(1)

    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    if(v->tamanho >= MAX_PROFESSOR){
        printf("Vetor de professores cheio.\n");
        return 0;
    }

    v->dados[v->tamanho] = p;
    v->tamanho++;

    return 1;
};

int removerP(VetorProfessores *v, int registro){ // O(n)

    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    int i = buscarP(v, registro);

    if(i == -1){
        printf("Professor com registro %d nao encontrado.\n", registro);
        return 0;
    }

    // desloca os professores posteriores para a esquerda
    for(int j = i; j < v->tamanho - 1; j++){
        v->dados[j] = v->dados[j + 1];
    }

    v->tamanho--;
    return 1;
};

int buscarP(VetorProfessores *v, int registro){ // O(n)

    if(v == NULL){
        return -1;
    }

    for(int i = 0; i < v->tamanho; i++){
        if(v->dados[i].registro == registro){
            return i;
        }
    }

    return -1;
};

void listarP(VetorProfessores *v){ // O(n * a)

    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return;
    }

    if(v->tamanho == 0){
        printf("Nao existem professores cadastrados.\n");
        return;
    }

    for(int i = 0; i < v->tamanho; i++){

        Professor *p = &v->dados[i];

        printf("\nNome: %s\n", p->nomeP);
        printf("Registro: %d\n", p->registro);
        printf("Quantidade de aulas: %d\n", p->qtdAulas);

        for(int j = 0; j < p->qtdAulas; j++){
            printf("Aula %d: %s | %s\n", j + 1,
                   p->aulas[j].nomeD,
                   p->aulas[j].horario);
        }
    }
};

int editarProfessor(VetorProfessores *v, int registro,
                    const char *nNome){ // O(n)

    if(v == NULL || nNome == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    int i = buscarP(v, registro);

    if(i == -1){
        printf("Professor nao encontrado.\n");
        return 0;
    }

    Professor *p = &v->dados[i];

    strncpy(p->nomeP, nNome, TAM_NOME - 1);
    p->nomeP[TAM_NOME - 1] = '\0';

    printf("Dados alterados com sucesso.\n");
    return 1;
};

int adicionarAula(VetorProfessores *v, int registro,
                  const char *disciplina,
                  const char *horario){ // O(n + a)

    if(v == NULL || disciplina == NULL || horario == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    int i = buscarP(v, registro);

    if(i == -1){
        printf("Professor nao encontrado.\n");
        return 0;
    }

    Professor *p = &v->dados[i];

    if(p->qtdAulas >= MAX_AULAS){
        printf("Limite de aulas atingido.\n");
        return 0;
    }

    // evita disciplina repetida para o mesmo professor
    for(int j = 0; j < p->qtdAulas; j++){
        if(strcmp(p->aulas[j].nomeD, disciplina) == 0){
            printf("Disciplina ja cadastrada para este professor.\n");
            return 0;
        }
    }

    strncpy(p->aulas[p->qtdAulas].nomeD, disciplina, TAM_DISCIPLINA - 1);
    p->aulas[p->qtdAulas].nomeD[TAM_DISCIPLINA - 1] = '\0';

    strncpy(p->aulas[p->qtdAulas].horario, horario, TAM_HORARIO - 1);
    p->aulas[p->qtdAulas].horario[TAM_HORARIO - 1] = '\0';

    p->qtdAulas++;

    return 1;
};

int removerAula(VetorProfessores *v, int registro,
                const char *disciplina){ // O(n + a)

    if(v == NULL || disciplina == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    int i = buscarP(v, registro);

    if(i == -1){
        printf("Professor nao encontrado.\n");
        return 0;
    }

    Professor *p = &v->dados[i];

    int j;

    for(j = 0; j < p->qtdAulas; j++){
        if(strcmp(p->aulas[j].nomeD, disciplina) == 0){
            break;
        }
    }

    if(j == p->qtdAulas){
        printf("Aula nao encontrada.\n");
        return 0;
    }

    for(int k = j; k < p->qtdAulas - 1; k++){
        p->aulas[k] = p->aulas[k + 1];
    }

    p->qtdAulas--;
    return 1;
};