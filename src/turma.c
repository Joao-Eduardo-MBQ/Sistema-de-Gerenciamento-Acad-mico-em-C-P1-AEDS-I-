#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/turma.h"
#include "../include/aluno.h"
#include "../include/professor.h"

void iniciarVetorTurmas(VetorTurmas *vt){
    if(vt == NULL){
        printf("Erro: vetor invalido.\n");
        return;
    }
    vt->tamanho = 0;
}

void iniciarTurma(Turma *t, int nTurma, const char *sala, const char *materia){
    if(t == NULL || sala == NULL || materia == NULL){
        printf("Erro: dados invalidos.\n");
        return;
    }

    memset(t, 0, sizeof(*t));
    t->nTurma = nTurma;
    strncpy(t->sala, sala, TAM_SALA - 1);
    strncpy(t->materia, materia, TAM_DISCIPLINA - 1);
    t->registroProf = -1;
    t->qtdAlunos = 0;
}

int buscarturma(VetorTurmas *vt, int nTurma){
    if(vt == NULL){
        return -1;
    }

    for(int i = 0; i < vt->tamanho; i++){
        if(vt->dados[i].nTurma == nTurma){
            return i;
        }
    }
    return -1;
}

int inserirTurma(VetorTurmas *vt, Turma t){
    if(vt == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    if(vt->tamanho >= MAX_TURMAS){
        printf("Vetor de turmas cheio.\n");
        return 0;
    }

    vt->dados[vt->tamanho] = t;
    vt->tamanho++;
    return 1;
}

int removerTurma(VetorTurmas *vt, int nTurma){
    if(vt == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    int i = buscarturma(vt, nTurma);
    if(i == -1){
        return 0;               /* o menu ja avisa que nao encontrou */
    }

    for(int j = i; j < vt->tamanho - 1; j++){
        vt->dados[j] = vt->dados[j + 1];
    }
    vt->tamanho--;
    return 1;
}

int adicionarAlunoTurma(VetorTurmas *vt, int nTurma, int matricula){
    if(vt == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    int i = buscarturma(vt, nTurma);
    if(i == -1){
        printf("Turma nao encontrada.\n");
        return 0;
    }

    Turma *t = &vt->dados[i];

    if(t->qtdAlunos >= MAX_ALUNOS_TURMA){
        printf("Turma cheia.\n");
        return 0;
    }

    for(int j = 0; j < t->qtdAlunos; j++){
        if(t->matriculas[j] == matricula){
            printf("Aluno ja matriculado nesta turma.\n");
            return 0;
        }
    }

    t->matriculas[t->qtdAlunos] = matricula;
    t->qtdAlunos++;
    return 1;
}

int removerAlunoTurma(VetorTurmas *vt, int nTurma, int matricula){
    if(vt == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    int i = buscarturma(vt, nTurma);
    if(i == -1){
        printf("Turma nao encontrada.\n");
        return 0;
    }

    Turma *t = &vt->dados[i];

    for(int j = 0; j < t->qtdAlunos; j++){
        if(t->matriculas[j] == matricula){
            for(int k = j; k < t->qtdAlunos - 1; k++){
                t->matriculas[k] = t->matriculas[k + 1];
            }
            t->qtdAlunos--;
            return 1;           /* o menu imprime a mensagem de sucesso */
        }
    }

    printf("Aluno nao encontrado nesta turma.\n");
    return 0;
}

void imprimirTurma(const Turma *t, VetorProfessores *vp){
    char nomeProf[TAM_NOME] = "(nenhum)";

    if(t->registroProf != -1){
        int p = buscarP(vp, t->registroProf);
        if(p != -1){
            strncpy(nomeProf, vp->dados[p].nomeP, TAM_NOME - 1);
            nomeProf[TAM_NOME - 1] = '\0';
        } else {
            strcpy(nomeProf, "(removido)");
        }
    }

    printf("\nTurma %d | Sala: %s | Materia: %s | Professor: %s | Qtd Alunos: %d\n",
           t->nTurma, t->sala, t->materia, nomeProf, t->qtdAlunos);

    for(int j = 0; j < t->qtdAlunos; j++){
        printf("Aluno %d: Matricula %d\n", j + 1, t->matriculas[j]);
    }
}

void listarTurmas(VetorTurmas *vt, VetorProfessores *vp){
    if(vt == NULL){
        printf("Erro: vetor invalido.\n");
        return;
    }

    for(int i = 0; i < vt->tamanho; i++){
        imprimirTurma(&vt->dados[i], vp);
    }
}

int designarProfessorTurma(VetorTurmas *vt, int nTurma, int registro){
    if(vt == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    int i = buscarturma(vt, nTurma);
    if(i == -1){
        printf("Turma nao encontrada.\n");
        return 0;
    }

    vt->dados[i].registroProf = registro;
    return 1;
}