#include <stdio.h>
#include <string.h>
#include "../include/turma.h"

void iniciarVetorTurmas(VetorTurmas *vt){
    if(vt == NULL){
        printf("Erro: vetor invalido.\n");
        return;
    }
    vt->tamanho = 0;
}

int buscarTurma(const VetorTurmas *vt, int codigo){
    if(vt == NULL){
        return -1;
    }

    for(int i = 0; i < vt->tamanho; i++){
        if(vt->dados[i].codigo == codigo){
            return i;
        }
    }
    return -1;
}

int cadastrarTurma(VetorTurmas *vt, const VetorDisciplinas *vd, const VetorProfessores *vp,
                   int codigo, int codDisciplina, int matProfessor,
                   const char *horario, const char *sala, int vagas){
    if(vt == NULL || vd == NULL || vp == NULL || horario == NULL || sala == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    if(codigo <= 0){
        printf("Codigo de turma invalido.\n");
        return 0;
    }

    if(buscarTurma(vt, codigo) != -1){
        printf("Turma ja cadastrada.\n");
        return 0;
    }

    if(buscarDisciplina(vd, codDisciplina) == -1){
        printf("Disciplina %d nao encontrada.\n", codDisciplina);
        return 0;
    }

    if(buscarP(vp, matProfessor) == -1){
        printf("Professor %d nao encontrado.\n", matProfessor);
        return 0;
    }

    if(vagas <= 0){
        printf("Numero de vagas invalido.\n");
        return 0;
    }

    if(vt->tamanho >= MAX_TURMAS){
        printf("Vetor de turmas cheio.\n");
        return 0;
    }

    /* conflitos de horario */
    for(int i = 0; i < vt->tamanho; i++){
        const Turma *o = &vt->dados[i];
        if(strcmp(o->horario, horario) != 0){
            continue;
        }
        if(strcmp(o->sala, sala) == 0){
            printf("A sala %s ja esta ocupada nesse horario (turma %d).\n", sala, o->codigo);
            return 0;
        }
        if(o->matProfessor == matProfessor){
            printf("O professor ja leciona nesse horario (turma %d).\n", o->codigo);
            return 0;
        }
    }

    Turma *t = &vt->dados[vt->tamanho];
    memset(t, 0, sizeof(*t));
    t->codigo = codigo;
    t->codDisciplina = codDisciplina;
    t->matProfessor = matProfessor;
    copiarStr(t->horario, sizeof(t->horario), horario);
    copiarStr(t->sala,    sizeof(t->sala),    sala);
    t->vagas = vagas;
    vt->tamanho++;
    return 1;
}

int removerTurma(VetorTurmas *vt, int codigo){
    if(vt == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    int i = buscarTurma(vt, codigo);
    if(i == -1){
        printf("Turma nao encontrada.\n");
        return 0;
    }

    for(int j = i; j < vt->tamanho - 1; j++){
        vt->dados[j] = vt->dados[j + 1];
    }
    vt->tamanho--;
    return 1;
}

void imprimirTurma(const Turma *t, const VetorDisciplinas *vd, const VetorProfessores *vp,
                   int ocupadas){
    const char *nomeDisc = "(removida)";
    const char *nomeProf = "(removido)";

    int d = buscarDisciplina(vd, t->codDisciplina);
    if(d != -1){
        nomeDisc = vd->dados[d].nome;
    }

    int p = buscarP(vp, t->matProfessor);
    if(p != -1){
        nomeProf = vp->dados[p].nome;
    }

    printf("Turma %d | Disciplina: %d - %s | Prof.: %s | Horario: %s | Sala: %s | Vagas: %d/%d\n",
           t->codigo, t->codDisciplina, nomeDisc, nomeProf, t->horario, t->sala,
           ocupadas, t->vagas);
}

int professorTemTurma(const VetorTurmas *vt, int matProfessor){
    if(vt == NULL){
        return 0;
    }

    for(int i = 0; i < vt->tamanho; i++){
        if(vt->dados[i].matProfessor == matProfessor){
            return 1;
        }
    }
    return 0;
}

int disciplinaTemTurma(const VetorTurmas *vt, int codDisciplina){
    if(vt == NULL){
        return 0;
    }

    for(int i = 0; i < vt->tamanho; i++){
        if(vt->dados[i].codDisciplina == codDisciplina){
            return 1;
        }
    }
    return 0;
}