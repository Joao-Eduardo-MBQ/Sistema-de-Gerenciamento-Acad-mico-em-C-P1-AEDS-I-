#include <stdio.h>
#include "../include/util.h"
#include "../include/aluno.h"
#include "../include/professor.h"
#include "../include/disciplina.h"
#include "../include/turma.h"
#include "../include/matricula.h"
#include "../include/fila.h"

/* Todo o estado do sistema em um unico lugar */
typedef struct {
    VetorAlunos      alunos;
    VetorProfessores professores;
    VetorDisciplinas disciplinas;
    VetorTurmas      turmas;
    VetorMatriculas  matriculas;
    FilaAtendimento  fila;
} Sistema;

/* Convencao: as funcoes dos modulos imprimem os ERROS;
   os menus imprimem as mensagens de SUCESSO. */

/* ============================ ALUNOS ============================ */

static void menuAluno(Sistema *s){
    int op;

    do{
        printf("\n----- ALUNOS -----\n");
        printf("1. Cadastrar\n");
        printf("2. Remover\n");
        printf("3. Consultar\n");
        printf("4. Listar\n");
        printf("5. Editar\n");
        printf("0. Voltar\n");
        op = lerInt("Opcao: ");

        switch(op){

        case 1: {
            Aluno a;
            char nome[TAM_NOME], curso[TAM_CURSO], periodo[TAM_PERIODO], email[TAM_EMAIL];
            int mat = lerInt("Matricula: ");
            if(buscarA(&s->alunos, mat) != -1){
                printf("Aluno ja cadastrado.\n");
                break;
            }
            lerString("Nome: ", nome, sizeof(nome));
            lerString("Curso: ", curso, sizeof(curso));
            lerString("Periodo (ex.: 2026.1): ", periodo, sizeof(periodo));
            lerString("E-mail: ", email, sizeof(email));
            if(iniciarAluno(&a, mat, nome, curso, periodo, email) && inserirA(&s->alunos, a)){
                printf("Aluno cadastrado.\n");
            }
            break;
        }

        case 2: {
            int mat = lerInt("Matricula: ");
            if(buscarA(&s->alunos, mat) == -1){
                printf("Aluno nao encontrado.\n");
                break;
            }
            if(alunoTemPendencias(&s->matriculas, mat) > 0){
                printf("Nao e possivel remover: o aluno possui matriculas em andamento.\n");
                break;
            }
            if(filaContem(&s->fila, mat)){
                printf("Nao e possivel remover: o aluno esta na fila de atendimento.\n");
                break;
            }
            if(removerA(&s->alunos, mat)){
                removerMatriculasDoAluno(&s->matriculas, mat);
                printf("Aluno removido.\n");
            }
            break;
        }

        case 3: {
            int i = buscarA(&s->alunos, lerInt("Matricula: "));
            if(i == -1){
                printf("Aluno nao encontrado.\n");
            } else {
                imprimirAluno(&s->alunos.dados[i]);
            }
            break;
        }

        case 4:
            listarA(&s->alunos);
            break;

        case 5: {
            char nome[TAM_NOME], curso[TAM_CURSO], periodo[TAM_PERIODO], email[TAM_EMAIL];
            int mat = lerInt("Matricula: ");
            if(buscarA(&s->alunos, mat) == -1){
                printf("Aluno nao encontrado.\n");
                break;
            }
            lerString("Novo nome: ", nome, sizeof(nome));
            lerString("Novo curso: ", curso, sizeof(curso));
            lerString("Novo periodo: ", periodo, sizeof(periodo));
            lerString("Novo e-mail: ", email, sizeof(email));
            if(editarAluno(&s->alunos, mat, nome, curso, periodo, email)){
                printf("Aluno atualizado.\n");
            }
            break;
        }

        case 0:
            break;

        default:
            printf("Opcao invalida.\n");
        }
    } while(op != 0);
}

/* ========================== DISCIPLINAS ========================== */

static void menuDisciplina(Sistema *s){
    int op;

    do{
        printf("\n----- DISCIPLINAS -----\n");
        printf("1. Cadastrar\n");
        printf("2. Remover\n");
        printf("3. Consultar por codigo\n");
        printf("4. Listar\n");
        printf("5. Editar\n");
        printf("6. Adicionar pre-requisito\n");
        printf("7. Remover pre-requisito\n");
        printf("0. Voltar\n");
        op = lerInt("Opcao: ");

        switch(op){

        case 1: {
            Disciplina d;
            char nome[TAM_DISCIPLINA], periodo[TAM_PERIODO];
            int cod = lerInt("Codigo: ");
            if(buscarDisciplina(&s->disciplinas, cod) != -1){
                printf("Codigo ja cadastrado.\n");
                break;
            }
            lerString("Nome: ", nome, sizeof(nome));
            int carga = lerInt("Carga horaria (h): ");
            lerString("Periodo (ex.: 2026.1): ", periodo, sizeof(periodo));
            int vagas = lerInt("Numero de vagas: ");
            if(iniciarDisciplina(&d, cod, nome, carga, periodo, vagas) &&
               inserirDisciplina(&s->disciplinas, d)){
                printf("Disciplina cadastrada.\n");
            }
            break;
        }

        case 2: {
            int cod = lerInt("Codigo: ");
            if(buscarDisciplina(&s->disciplinas, cod) == -1){
                printf("Disciplina nao encontrada.\n");
                break;
            }
            if(disciplinaTemTurma(&s->turmas, cod)){
                printf("Nao e possivel remover: existem turmas desta disciplina.\n");
                break;
            }
            if(removerDisciplina(&s->disciplinas, cod)){
                printf("Disciplina removida.\n");
            }
            break;
        }

        case 3: {
            int i = buscarDisciplina(&s->disciplinas, lerInt("Codigo: "));
            if(i == -1){
                printf("Disciplina nao encontrada.\n");
            } else {
                imprimirDisciplina(&s->disciplinas.dados[i]);
            }
            break;
        }

        case 4:
            listarDisciplinas(&s->disciplinas);
            break;

        case 5: {
            char nome[TAM_DISCIPLINA], periodo[TAM_PERIODO];
            int cod = lerInt("Codigo: ");
            if(buscarDisciplina(&s->disciplinas, cod) == -1){
                printf("Disciplina nao encontrada.\n");
                break;
            }
            lerString("Novo nome: ", nome, sizeof(nome));
            int carga = lerInt("Nova carga horaria (h): ");
            lerString("Novo periodo: ", periodo, sizeof(periodo));
            int vagas = lerInt("Novo numero de vagas: ");
            if(editarDisciplina(&s->disciplinas, cod, nome, carga, periodo, vagas)){
                printf("Disciplina atualizada.\n");
            }
            break;
        }

        case 6: {
            int cod = lerInt("Codigo da disciplina: ");
            int pre = lerInt("Codigo do pre-requisito: ");
            if(adicionarPrerequisito(&s->disciplinas, cod, pre)){
                printf("Pre-requisito adicionado.\n");
            }
            break;
        }

        case 7: {
            int cod = lerInt("Codigo da disciplina: ");
            int pre = lerInt("Codigo do pre-requisito: ");
            if(removerPrerequisito(&s->disciplinas, cod, pre)){
                printf("Pre-requisito removido.\n");
            }
            break;
        }

        case 0:
            break;

        default:
            printf("Opcao invalida.\n");
        }
    } while(op != 0);
}

/* =========================== PROFESSORES =========================== */

static void menuProfessor(Sistema *s){
    int op;

    do{
        printf("\n----- PROFESSORES -----\n");
        printf("1. Cadastrar\n");
        printf("2. Remover\n");
        printf("3. Consultar\n");
        printf("4. Listar\n");
        printf("5. Editar\n");
        printf("0. Voltar\n");
        op = lerInt("Opcao: ");

        switch(op){

        case 1: {
            Professor p;
            char nome[TAM_NOME], area[TAM_AREA], email[TAM_EMAIL];
            int mat = lerInt("Matricula: ");
            if(buscarP(&s->professores, mat) != -1){
                printf("Professor ja cadastrado.\n");
                break;
            }
            lerString("Nome: ", nome, sizeof(nome));
            lerString("Area de atuacao: ", area, sizeof(area));
            lerString("E-mail: ", email, sizeof(email));
            if(iniciarProfessor(&p, mat, nome, area, email) && inserirP(&s->professores, p)){
                printf("Professor cadastrado.\n");
            }
            break;
        }

        case 2: {
            int mat = lerInt("Matricula: ");
            if(buscarP(&s->professores, mat) == -1){
                printf("Professor nao encontrado.\n");
                break;
            }
            if(professorTemTurma(&s->turmas, mat)){
                printf("Nao e possivel remover: o professor possui turmas.\n");
                break;
            }
            if(removerP(&s->professores, mat)){
                printf("Professor removido.\n");
            }
            break;
        }

        case 3: {
            int i = buscarP(&s->professores, lerInt("Matricula: "));
            if(i == -1){
                printf("Professor nao encontrado.\n");
            } else {
                imprimirProfessor(&s->professores.dados[i]);
            }
            break;
        }

        case 4:
            listarP(&s->professores);
            break;

        case 5: {
            char nome[TAM_NOME], area[TAM_AREA], email[TAM_EMAIL];
            int mat = lerInt("Matricula: ");
            if(buscarP(&s->professores, mat) == -1){
                printf("Professor nao encontrado.\n");
                break;
            }
            lerString("Novo nome: ", nome, sizeof(nome));
            lerString("Nova area de atuacao: ", area, sizeof(area));
            lerString("Novo e-mail: ", email, sizeof(email));
            if(editarProfessor(&s->professores, mat, nome, area, email)){
                printf("Professor atualizado.\n");
            }
            break;
        }

        case 0:
            break;

        default:
            printf("Opcao invalida.\n");
        }
    } while(op != 0);
}

/* ============================= TURMAS ============================= */

static void menuTurma(Sistema *s){
    int op;

    do{
        printf("\n----- TURMAS -----\n");
        printf("1. Cadastrar\n");
        printf("2. Remover\n");
        printf("3. Consultar\n");
        printf("4. Listar\n");
        printf("0. Voltar\n");
        op = lerInt("Opcao: ");

        switch(op){

        case 1: {
            char horario[TAM_HORARIO], sala[TAM_SALA];
            int cod  = lerInt("Codigo da turma: ");
            if(buscarTurma(&s->turmas, cod) != -1){
                printf("Turma ja cadastrada.\n");
                break;
            }
            int disc = lerInt("Codigo da disciplina: ");
            int prof = lerInt("Matricula do professor: ");
            lerString("Horario (ex.: Seg 08:00-10:00): ", horario, sizeof(horario));
            lerString("Sala: ", sala, sizeof(sala));
            int vagas = lerInt("Numero de vagas: ");
            if(cadastrarTurma(&s->turmas, &s->disciplinas, &s->professores,
                              cod, disc, prof, horario, sala, vagas)){
                printf("Turma cadastrada.\n");
            }
            break;
        }

        case 2: {
            int cod = lerInt("Codigo da turma: ");
            if(buscarTurma(&s->turmas, cod) == -1){
                printf("Turma nao encontrada.\n");
                break;
            }
            if(contarAlunosTurma(&s->matriculas, cod) > 0){
                printf("Nao e possivel remover: a turma possui alunos matriculados.\n");
                break;
            }
            if(removerTurma(&s->turmas, cod)){
                printf("Turma removida.\n");
            }
            break;
        }

        case 3: {
            int cod = lerInt("Codigo da turma: ");
            int i = buscarTurma(&s->turmas, cod);
            if(i == -1){
                printf("Turma nao encontrada.\n");
            } else {
                imprimirTurma(&s->turmas.dados[i], &s->disciplinas, &s->professores,
                              contarAlunosTurma(&s->matriculas, cod));
            }
            break;
        }

        case 4:
            if(s->turmas.tamanho == 0){
                printf("Nenhuma turma cadastrada.\n");
            }
            for(int i = 0; i < s->turmas.tamanho; i++){
                imprimirTurma(&s->turmas.dados[i], &s->disciplinas, &s->professores,
                              contarAlunosTurma(&s->matriculas, s->turmas.dados[i].codigo));
            }
            break;

        case 0:
            break;

        default:
            printf("Opcao invalida.\n");
        }
    } while(op != 0);
}

/* ====================== MATRICULAS, NOTAS E FREQUENCIA ====================== */

static void menuMatricula(Sistema *s){
    int op;

    do{
        printf("\n----- MATRICULAS -----\n");
        printf("1. Matricular aluno\n");
        printf("2. Cancelar matricula\n");
        printf("3. Registrar nota\n");
        printf("4. Registrar frequencia\n");
        printf("0. Voltar\n");
        op = lerInt("Opcao: ");

        switch(op){

        case 1: {
            char semestre[TAM_SEMESTRE];
            int mat   = lerInt("Matricula do aluno: ");
            int turma = lerInt("Codigo da turma: ");
            lerString("Semestre (ex.: 2026.1): ", semestre, sizeof(semestre));
            if(matricularAluno(&s->matriculas, &s->alunos, &s->turmas, &s->disciplinas,
                               mat, turma, semestre)){
                printf("Aluno matriculado.\n");
            }
            break;
        }

        case 2: {
            int mat   = lerInt("Matricula do aluno: ");
            int turma = lerInt("Codigo da turma: ");
            if(cancelarMatricula(&s->matriculas, mat, turma)){
                printf("Matricula cancelada.\n");
            }
            break;
        }

        case 3: {
            int mat   = lerInt("Matricula do aluno: ");
            int turma = lerInt("Codigo da turma: ");
            float nota = lerFloat("Nota (0 a 10): ");
            if(registrarNota(&s->matriculas, mat, turma, nota)){
                int i = buscarMatricula(&s->matriculas, mat, turma);
                printf("Nota registrada. Situacao: %s\n",
                       nomeSituacao(s->matriculas.dados[i].situacao));
            }
            break;
        }

        case 4: {
            int mat   = lerInt("Matricula do aluno: ");
            int turma = lerInt("Codigo da turma: ");
            float freq = lerFloat("Frequencia (0 a 100): ");
            if(registrarFrequencia(&s->matriculas, mat, turma, freq)){
                int i = buscarMatricula(&s->matriculas, mat, turma);
                printf("Frequencia registrada. Situacao: %s\n",
                       nomeSituacao(s->matriculas.dados[i].situacao));
            }
            break;
        }

        case 0:
            break;

        default:
            printf("Opcao invalida.\n");
        }
    } while(op != 0);
}

/* ======================= FILA DE ATENDIMENTO ======================= */

static void menuFila(Sistema *s){
    int op;

    do{
        printf("\n----- FILA DE ATENDIMENTO -----\n");
        printf("1. Inserir aluno na fila\n");
        printf("2. Atender proximo\n");
        printf("3. Ver proximo\n");
        printf("4. Listar fila\n");
        printf("0. Voltar\n");
        op = lerInt("Opcao: ");

        switch(op){

        case 1:
            if(entrarNaFila(&s->fila, &s->alunos, lerInt("Matricula do aluno: "))){
                printf("Aluno inserido na fila (posicao %d).\n", s->fila.tamanho);
            }
            break;

        case 2:
            atenderProximo(&s->fila, &s->alunos);
            break;

        case 3:
            proximoDaFila(&s->fila, &s->alunos);
            break;

        case 4:
            listarFila(&s->fila, &s->alunos);
            break;

        case 0:
            break;

        default:
            printf("Opcao invalida.\n");
        }
    } while(op != 0);
}

/* ============================ CONSULTAS ============================ */

static void menuConsultas(Sistema *s){
    int op;

    do{
        printf("\n----- CONSULTAS -----\n");
        printf("1. Situacao academica de um aluno\n");
        printf("2. Alunos de uma turma\n");
        printf("3. Disciplinas de um aluno\n");
        printf("4. Historico academico\n");
        printf("5. Pre-requisitos de uma disciplina\n");
        printf("0. Voltar\n");
        op = lerInt("Opcao: ");

        switch(op){

        case 1:
            consultarSituacaoAcademica(&s->matriculas, &s->alunos, lerInt("Matricula do aluno: "));
            break;

        case 2:
            listarAlunosTurma(&s->matriculas, &s->alunos, &s->turmas, lerInt("Codigo da turma: "));
            break;

        case 3:
            listarDisciplinasAluno(&s->matriculas, &s->alunos, &s->turmas, &s->disciplinas,
                                   lerInt("Matricula do aluno: "));
            break;

        case 4:
            historicoAcademico(&s->matriculas, &s->alunos, &s->turmas, &s->disciplinas,
                               lerInt("Matricula do aluno: "));
            break;

        case 5:
            listarPrerequisitos(&s->disciplinas, lerInt("Codigo da disciplina: "));
            break;

        case 0:
            break;

        default:
            printf("Opcao invalida.\n");
        }
    } while(op != 0);
}

/* ============================== MAIN ============================== */

int main(void){
    static Sistema sis;
    int op;

    iniciarA(&sis.alunos);
    iniciarP(&sis.professores);
    iniciarVetorDisciplinas(&sis.disciplinas);
    iniciarVetorTurmas(&sis.turmas);
    iniciarVetorMatriculas(&sis.matriculas);
    iniciarFila(&sis.fila);

    do{
        printf("\n===== SISTEMA ACADEMICO =====\n");
        printf("1. Alunos\n");
        printf("2. Disciplinas\n");
        printf("3. Professores\n");
        printf("4. Turmas\n");
        printf("5. Matriculas, notas e frequencia\n");
        printf("6. Fila de atendimento\n");
        printf("7. Consultas\n");
        printf("0. Sair\n");
        op = lerInt("Opcao: ");

        switch(op){
        case 1: menuAluno(&sis);       break;
        case 2: menuDisciplina(&sis);  break;
        case 3: menuProfessor(&sis);   break;
        case 4: menuTurma(&sis);       break;
        case 5: menuMatricula(&sis);   break;
        case 6: menuFila(&sis);        break;
        case 7: menuConsultas(&sis);   break;
        case 0: printf("Encerrando...\n"); break;
        default: printf("Opcao invalida.\n");
        }
    } while(op != 0);

    return 0;
}