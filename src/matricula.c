#include <stdio.h>
#include <string.h>
#include "../include/matricula.h"

void iniciarVetorMatriculas(VetorMatriculas *vm){
    if(vm == NULL){
        printf("Erro: vetor invalido.\n");
        return;
    }
    vm->tamanho = 0;
}

const char *nomeSituacao(Situacao s){
    switch(s){
        case SIT_CURSANDO:  return "Cursando";
        case SIT_APROVADO:  return "Aprovado";
        case SIT_REPROVADO: return "Reprovado";
        case SIT_CANCELADO: return "Cancelado";
    }
    return "?";
}

/* ultima matricula (nao cancelada) do aluno na turma */
int buscarMatricula(const VetorMatriculas *vm, int matAluno, int codTurma){
    if(vm == NULL){
        return -1;
    }

    for(int i = vm->tamanho - 1; i >= 0; i--){
        const Matricula *m = &vm->dados[i];
        if(m->matAluno == matAluno && m->codTurma == codTurma &&
           m->situacao != SIT_CANCELADO){
            return i;
        }
    }
    return -1;
}

/* o aluno tem alguma matricula com a situacao s em turmas desta disciplina? */
static int alunoTemSituacaoNaDisciplina(const VetorMatriculas *vm, const VetorTurmas *vt,
                                        int matAluno, int codDisc, Situacao s){
    for(int i = 0; i < vm->tamanho; i++){
        const Matricula *m = &vm->dados[i];
        if(m->matAluno != matAluno || m->situacao != s){
            continue;
        }

        int t = buscarTurma(vt, m->codTurma);
        if(t != -1 && vt->dados[t].codDisciplina == codDisc){
            return 1;
        }
    }
    return 0;
}

int contarAlunosTurma(const VetorMatriculas *vm, int codTurma){
    if(vm == NULL){
        return 0;
    }

    int n = 0;
    for(int i = 0; i < vm->tamanho; i++){
        if(vm->dados[i].codTurma == codTurma && vm->dados[i].situacao != SIT_CANCELADO){
            n++;
        }
    }
    return n;
}

int alunoTemPendencias(const VetorMatriculas *vm, int matAluno){
    if(vm == NULL){
        return 0;
    }

    int n = 0;
    for(int i = 0; i < vm->tamanho; i++){
        if(vm->dados[i].matAluno == matAluno && vm->dados[i].situacao == SIT_CURSANDO){
            n++;
        }
    }
    return n;
}

void removerMatriculasDoAluno(VetorMatriculas *vm, int matAluno){
    if(vm == NULL){
        return;
    }

    int k = 0;
    for(int i = 0; i < vm->tamanho; i++){
        if(vm->dados[i].matAluno != matAluno){
            vm->dados[k++] = vm->dados[i];
        }
    }
    vm->tamanho = k;
}

int matricularAluno(VetorMatriculas *vm, const VetorAlunos *va, const VetorTurmas *vt,
                    const VetorDisciplinas *vd, int matAluno, int codTurma,
                    const char *semestre){
    if(vm == NULL || va == NULL || vt == NULL || vd == NULL || semestre == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    if(buscarA(va, matAluno) == -1){
        printf("Aluno nao encontrado.\n");
        return 0;
    }

    int ti = buscarTurma(vt, codTurma);
    if(ti == -1){
        printf("Turma nao encontrada.\n");
        return 0;
    }
    const Turma *turma = &vt->dados[ti];

    int di = buscarDisciplina(vd, turma->codDisciplina);
    if(di == -1){
        printf("A disciplina da turma nao existe mais.\n");
        return 0;
    }
    const Disciplina *disc = &vd->dados[di];

    if(alunoTemSituacaoNaDisciplina(vm, vt, matAluno, disc->codigo, SIT_CURSANDO)){
        printf("O aluno ja esta cursando esta disciplina.\n");
        return 0;
    }

    if(alunoTemSituacaoNaDisciplina(vm, vt, matAluno, disc->codigo, SIT_APROVADO)){
        printf("O aluno ja foi aprovado nesta disciplina.\n");
        return 0;
    }

    /* pre-requisitos: o aluno precisa ter sido aprovado em todos */
    int faltando = 0;
    for(int k = 0; k < disc->qtdPrereq; k++){
        int cod = disc->prerequisitos[k];
        if(!alunoTemSituacaoNaDisciplina(vm, vt, matAluno, cod, SIT_APROVADO)){
            int p = buscarDisciplina(vd, cod);
            printf("Pre-requisito nao cumprido: %d - %s\n", cod,
                   p != -1 ? vd->dados[p].nome : "(removida)");
            faltando = 1;
        }
    }
    if(faltando){
        return 0;
    }

    /* conflito de horario com turmas que o aluno esta cursando */
    for(int i = 0; i < vm->tamanho; i++){
        const Matricula *m = &vm->dados[i];
        if(m->matAluno != matAluno || m->situacao != SIT_CURSANDO){
            continue;
        }

        int o = buscarTurma(vt, m->codTurma);
        if(o != -1 && strcmp(vt->dados[o].horario, turma->horario) == 0){
            printf("Conflito de horario com a turma %d.\n", m->codTurma);
            return 0;
        }
    }

    if(contarAlunosTurma(vm, codTurma) >= turma->vagas){
        printf("Turma sem vagas.\n");
        return 0;
    }

    if(vm->tamanho >= MAX_MATRICULAS){
        printf("Limite de matriculas atingido.\n");
        return 0;
    }

    Matricula *m = &vm->dados[vm->tamanho];
    memset(m, 0, sizeof(*m));
    m->matAluno = matAluno;
    m->codTurma = codTurma;
    strncpy(m->semestre, semestre, sizeof(m->semestre) - 1);
    m->semestre[sizeof(m->semestre) - 1] = '\0';
    m->situacao = SIT_CURSANDO;
    vm->tamanho++;
    return 1;
}

int cancelarMatricula(VetorMatriculas *vm, int matAluno, int codTurma){
    if(vm == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    int i = buscarMatricula(vm, matAluno, codTurma);
    if(i == -1){
        printf("Matricula nao encontrada.\n");
        return 0;
    }

    if(vm->dados[i].situacao != SIT_CURSANDO){
        printf("So e possivel cancelar uma matricula em andamento.\n");
        return 0;
    }

    vm->dados[i].situacao = SIT_CANCELADO;
    return 1;
}

/* define a situacao: so decide aprovado/reprovado quando nota e frequencia existem */
static void atualizarSituacao(Matricula *m){
    if(m->situacao == SIT_CANCELADO){
        return;
    }

    if(m->notaLancada && m->freqLancada){
        if(m->nota >= NOTA_MINIMA && m->frequencia >= FREQ_MINIMA){
            m->situacao = SIT_APROVADO;
        } else {
            m->situacao = SIT_REPROVADO;
        }
    } else {
        m->situacao = SIT_CURSANDO;
    }
}

int registrarNota(VetorMatriculas *vm, int matAluno, int codTurma, float nota){
    if(vm == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    if(!(nota >= 0.0f && nota <= 10.0f)){
        printf("Nota invalida (use 0 a 10).\n");
        return 0;
    }

    int i = buscarMatricula(vm, matAluno, codTurma);
    if(i == -1){
        printf("Matricula nao encontrada.\n");
        return 0;
    }

    vm->dados[i].nota = nota;
    vm->dados[i].notaLancada = 1;
    atualizarSituacao(&vm->dados[i]);
    return 1;
}

int registrarFrequencia(VetorMatriculas *vm, int matAluno, int codTurma, float freq){
    if(vm == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    if(!(freq >= 0.0f && freq <= 100.0f)){
        printf("Frequencia invalida (use 0 a 100).\n");
        return 0;
    }

    int i = buscarMatricula(vm, matAluno, codTurma);
    if(i == -1){
        printf("Matricula nao encontrada.\n");
        return 0;
    }

    vm->dados[i].frequencia = freq;
    vm->dados[i].freqLancada = 1;
    atualizarSituacao(&vm->dados[i]);
    return 1;
}

/* ----------------------------- consultas ----------------------------- */

static void imprimirLinha(const Matricula *m, const VetorTurmas *vt, const VetorDisciplinas *vd){
    char disc[96] = "(turma removida)";
    char nota[48] = "-";
    char freq[48] = "-";

    int t = buscarTurma(vt, m->codTurma);
    if(t != -1){
        int cod = vt->dados[t].codDisciplina;
        int d = buscarDisciplina(vd, cod);
        snprintf(disc, sizeof(disc), "%d - %s", cod,
                 d != -1 ? vd->dados[d].nome : "(removida)");
    }

    if(m->notaLancada){
        snprintf(nota, sizeof(nota), "%.1f", m->nota);
    }
    if(m->freqLancada){
        snprintf(freq, sizeof(freq), "%.1f%%", m->frequencia);
    }

    printf("%s | Turma %d | %s | Nota: %s | Freq.: %s | %s\n",
           m->semestre, m->codTurma, disc, nota, freq, nomeSituacao(m->situacao));
}

void consultarSituacaoAcademica(const VetorMatriculas *vm, const VetorAlunos *va, int matAluno){
    if(vm == NULL || va == NULL){
        printf("Erro: dados invalidos.\n");
        return;
    }

    int a = buscarA(va, matAluno);
    if(a == -1){
        printf("Aluno nao encontrado.\n");
        return;
    }

    int cont[4] = {0, 0, 0, 0};
    float soma = 0.0f;
    int   nNotas = 0;

    for(int i = 0; i < vm->tamanho; i++){
        const Matricula *m = &vm->dados[i];
        if(m->matAluno != matAluno){
            continue;
        }
        cont[m->situacao]++;
        if(m->notaLancada && m->situacao != SIT_CANCELADO){
            soma += m->nota;
            nNotas++;
        }
    }

    printf("\nSituacao academica de %s (matricula %d)\n", va->dados[a].nome, matAluno);
    printf("Curso: %s | Periodo: %s\n", va->dados[a].curso, va->dados[a].periodo);
    printf("Cursando: %d | Aprovadas: %d | Reprovadas: %d | Canceladas: %d\n",
           cont[SIT_CURSANDO], cont[SIT_APROVADO], cont[SIT_REPROVADO], cont[SIT_CANCELADO]);

    if(nNotas > 0){
        printf("Media das notas lancadas: %.2f\n", soma / nNotas);
    } else {
        printf("Nenhuma nota lancada ainda.\n");
    }
}

void listarAlunosTurma(const VetorMatriculas *vm, const VetorAlunos *va,
                       const VetorTurmas *vt, int codTurma){
    if(vm == NULL || va == NULL || vt == NULL){
        printf("Erro: dados invalidos.\n");
        return;
    }

    if(buscarTurma(vt, codTurma) == -1){
        printf("Turma nao encontrada.\n");
        return;
    }

    int n = 0;
    printf("\nAlunos da turma %d:\n", codTurma);
    for(int i = 0; i < vm->tamanho; i++){
        const Matricula *m = &vm->dados[i];
        if(m->codTurma != codTurma || m->situacao == SIT_CANCELADO){
            continue;
        }

        int a = buscarA(va, m->matAluno);
        printf("  %d - %s | %s\n", m->matAluno,
               a != -1 ? va->dados[a].nome : "(removido)", nomeSituacao(m->situacao));
        n++;
    }

    if(n == 0){
        printf("  Nenhum aluno matriculado.\n");
    }
}

void listarDisciplinasAluno(const VetorMatriculas *vm, const VetorAlunos *va,
                            const VetorTurmas *vt, const VetorDisciplinas *vd, int matAluno){
    if(vm == NULL || va == NULL || vt == NULL || vd == NULL){
        printf("Erro: dados invalidos.\n");
        return;
    }

    int a = buscarA(va, matAluno);
    if(a == -1){
        printf("Aluno nao encontrado.\n");
        return;
    }

    int n = 0;
    printf("\nDisciplinas de %s (em andamento):\n", va->dados[a].nome);
    for(int i = 0; i < vm->tamanho; i++){
        const Matricula *m = &vm->dados[i];
        if(m->matAluno != matAluno || m->situacao != SIT_CURSANDO){
            continue;
        }

        int t = buscarTurma(vt, m->codTurma);
        if(t == -1){
            continue;
        }

        const Turma *turma = &vt->dados[t];
        int d = buscarDisciplina(vd, turma->codDisciplina);
        printf("  %d - %s | Turma %d | %s | Sala %s\n", turma->codDisciplina,
               d != -1 ? vd->dados[d].nome : "(removida)", turma->codigo,
               turma->horario, turma->sala);
        n++;
    }

    if(n == 0){
        printf("  Nenhuma disciplina em andamento.\n");
    }
}

void historicoAcademico(const VetorMatriculas *vm, const VetorAlunos *va,
                        const VetorTurmas *vt, const VetorDisciplinas *vd, int matAluno){
    if(vm == NULL || va == NULL || vt == NULL || vd == NULL){
        printf("Erro: dados invalidos.\n");
        return;
    }

    int a = buscarA(va, matAluno);
    if(a == -1){
        printf("Aluno nao encontrado.\n");
        return;
    }

    int n = 0;
    printf("\nHistorico academico de %s (matricula %d):\n", va->dados[a].nome, matAluno);
    for(int i = 0; i < vm->tamanho; i++){
        if(vm->dados[i].matAluno == matAluno){
            printf("  ");
            imprimirLinha(&vm->dados[i], vt, vd);
            n++;
        }
    }

    if(n == 0){
        printf("  Nenhum registro.\n");
    }
}