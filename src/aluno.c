#include "../include/aluno.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void iniciarA(VetorAlunos *v){ // O(1)

    // inicializa o vetor vazio
    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return;
    }

    v->tamanho = 0;
};

int inserirA(VetorAlunos *v, Aluno a){ // O(1)

    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    // verifica se o vetor esta cheio
    if(v->tamanho >= MAX_ALUNO){
        printf("Vetor de alunos cheio.\n");
        return 0;
    }

    // adiciona o aluno na ultima posicao
    v->dados[v->tamanho] = a;
    v->tamanho++;

    return 1;
};

int removerA(VetorAlunos *v, int matricula){ // O(n)

    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    // busca o aluno pela matricula
    int i = buscarA(v, matricula);

    if(i == -1){
        printf("Aluno com matricula %d nao encontrado.\n", matricula);
        return 0;
    }

    // desloca os alunos posteriores para a esquerda
    for(int j = i; j < v->tamanho - 1; j++){
        v->dados[j] = v->dados[j + 1];
    }

    v->tamanho--;
    return 1;
};

int buscarA(VetorAlunos *v, int matricula){ // O(n)

    if(v == NULL){
        return -1;
    }

    // procura o aluno pela matricula
    for(int i = 0; i < v->tamanho; i++){
        if(v->dados[i].matricula == matricula){
            return i;
        }
    }

    return -1;
};

void listarA(VetorAlunos *v){ // O(n * d * p)

    if(v == NULL){
        printf("Erro: vetor invalido.\n");
        return;
    }

    if(v->tamanho == 0){
        printf("Nao existem alunos cadastrados.\n");
        return;
    }

    // percorre os alunos cadastrados
    for(int i = 0; i < v->tamanho; i++){

        Aluno *a = &v->dados[i];

        printf("\nNome: %s\n", a->nomeA);
        printf("Idade: %d\n", a->idadeA);
        printf("Matricula: %d\n", a->matricula);
        printf("Curso: %s\n", a->curso);
        printf("Quantidade de disciplinas: %d\n", a->qtdD);

        // percorre as disciplinas e suas notas
        for(int j = 0; j < a->qtdD; j++){
            printf("\nDisciplina: %s\n", a->ds[j].nomeD);

            for(int z = 0; z < a->ds[j].qtdN; z++){
                printf("P%d: %.2f\n", z + 1, a->ds[j].notas[z]);
            }
        }
    }
};

int editarAluno(VetorAlunos *v, int matricula, const char *nNome, int nIdade, const char *nCurso){ // O(n)

    if(v == NULL || nNome == NULL || nCurso == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    // busca o aluno pela matricula
    int i = buscarA(v, matricula);

    if(i == -1){
        printf("Aluno nao encontrado.\n");
        return 0;
    }

    Aluno *a = &v->dados[i];

    // atualiza os dados do aluno
    strncpy(a->nomeA, nNome, TAM_NOME - 1);
    a->nomeA[TAM_NOME - 1] = '\0';

    a->idadeA = nIdade;

    strncpy(a->curso, nCurso, TAM_CURSO - 1);
    a->curso[TAM_CURSO - 1] = '\0';

    printf("Dados alterados com sucesso.\n");
    return 1;
};

int adicionarDisciplina(VetorAlunos *v, int matricula, const char *nomeD){ // O(n)

};

int removerDisciplina(VetorAlunos *v, int matricula, const char *nomeD){ // O(n + d)

};

int lancarNota(VetorAlunos *v, int matricula, const char *nomeD, int prova, float nota){ // O(n + d)

    if(v == NULL || nomeD == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    if(prova < 1 || prova > MAX_PROVAS){
        printf("Numero de prova invalido.\n");
        return 0;
    }

    // busca o aluno pela matricula
    int i = buscarA(v, matricula);

    if(i == -1){
        printf("Aluno nao encontrado.\n");
        return 0;
    }

    Aluno *a = &v->dados[i];

    // procura a disciplina e registra a nota
    for(int d = 0; d < a->qtdD; d++){
        if(strcmp(a->ds[d].nomeD, nomeD) == 0){

            a->ds[d].notas[prova - 1] = nota;

            if(prova > a->ds[d].qtdN){
                a->ds[d].qtdN = prova;
            }

            printf("Nota lancada com sucesso.\n");
            return 1;
        }
    }

    printf("Disciplina nao encontrada.\n");
    return 0;
};