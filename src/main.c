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

/* le a opcao do menu; se digitar letra, descarta a linha e devolve -1 */
static int lerOpcao(void){
    int op = -1;
    int r = scanf("%d", &op);

    if(r == EOF){
        return 0;
    }
    if(r != 1){
        int c;
        while((c = getchar()) != '\n' && c != EOF){ }
        return -1;
    }
    return op;
}

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
        printf("Opcao: ");
        op = lerOpcao();

        switch(op){

        case 1: {
            Aluno a;
            char nome[TAM_NOME] = "", curso[TAM_CURSO] = "";
            char periodo[TAM_PERIODO] = "", email[TAM_EMAIL] = "";
            int mat = 0;

            printf("Matricula: ");
            scanf("%d", &mat);
            if(buscarA(&s->alunos, mat) != -1){
                printf("Aluno ja cadastrado.\n");
                break;
            }
            printf("Nome: ");
            scanf(" %99[^\n]", nome);
            printf("Curso: ");
            scanf(" %49[^\n]", curso);
            printf("Periodo (ex.: 2026.1): ");
            scanf(" %9[^\n]", periodo);
            printf("E-mail: ");
            scanf(" %99[^\n]", email);

            if(iniciarAluno(&a, mat, nome, curso, periodo, email) && inserirA(&s->alunos, a)){
                printf("Aluno cadastrado.\n");
            }
            break;
        }

        case 2: {
            int mat = 0;

            printf("Matricula: ");
            scanf("%d", &mat);
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
            int mat = 0, i;

            printf("Matricula: ");
            scanf("%d", &mat);
            i = buscarA(&s->alunos, mat);
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
            char nome[TAM_NOME] = "", curso[TAM_CURSO] = "";
            char periodo[TAM_PERIODO] = "", email[TAM_EMAIL] = "";
            int mat = 0;

            printf("Matricula: ");
            scanf("%d", &mat);
            if(buscarA(&s->alunos, mat) == -1){
                printf("Aluno nao encontrado.\n");
                break;
            }
            printf("Novo nome: ");
            scanf(" %99[^\n]", nome);
            printf("Novo curso: ");
            scanf(" %49[^\n]", curso);
            printf("Novo periodo: ");
            scanf(" %9[^\n]", periodo);
            printf("Novo e-mail: ");
            scanf(" %99[^\n]", email);

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
        printf("Opcao: ");
        op = lerOpcao();

        switch(op){

        case 1: {
            Disciplina d;
            char nome[TAM_DISCIPLINA] = "", periodo[TAM_PERIODO] = "";
            int cod = 0, carga = 0, vagas = 0;

            printf("Codigo: ");
            scanf("%d", &cod);
            if(buscarDisciplina(&s->disciplinas, cod) != -1){
                printf("Codigo ja cadastrado.\n");
                break;
            }
            printf("Nome: ");
            scanf(" %49[^\n]", nome);
            printf("Carga horaria (h): ");
            scanf("%d", &carga);
            printf("Periodo (ex.: 2026.1): ");
            scanf(" %9[^\n]", periodo);
            printf("Numero de vagas: ");
            scanf("%d", &vagas);

            if(iniciarDisciplina(&d, cod, nome, carga, periodo, vagas) &&
               inserirDisciplina(&s->disciplinas, d)){
                printf("Disciplina cadastrada.\n");
            }
            break;
        }

        case 2: {
            int cod = 0;

            printf("Codigo: ");
            scanf("%d", &cod);
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
            int cod = 0, i;

            printf("Codigo: ");
            scanf("%d", &cod);
            i = buscarDisciplina(&s->disciplinas, cod);
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
            char nome[TAM_DISCIPLINA] = "", periodo[TAM_PERIODO] = "";
            int cod = 0, carga = 0, vagas = 0;

            printf("Codigo: ");
            scanf("%d", &cod);
            if(buscarDisciplina(&s->disciplinas, cod) == -1){
                printf("Disciplina nao encontrada.\n");
                break;
            }
            printf("Novo nome: ");
            scanf(" %49[^\n]", nome);
            printf("Nova carga horaria (h): ");
            scanf("%d", &carga);
            printf("Novo periodo: ");
            scanf(" %9[^\n]", periodo);
            printf("Novo numero de vagas: ");
            scanf("%d", &vagas);

            if(editarDisciplina(&s->disciplinas, cod, nome, carga, periodo, vagas)){
                printf("Disciplina atualizada.\n");
            }
            break;
        }

        case 6: {
            int cod = 0, pre = 0;

            printf("Codigo da disciplina: ");
            scanf("%d", &cod);
            printf("Codigo do pre-requisito: ");
            scanf("%d", &pre);
            if(adicionarPrerequisito(&s->disciplinas, cod, pre)){
                printf("Pre-requisito adicionado.\n");
            }
            break;
        }

        case 7: {
            int cod = 0, pre = 0;

            printf("Codigo da disciplina: ");
            scanf("%d", &cod);
            printf("Codigo do pre-requisito: ");
            scanf("%d", &pre);
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
        printf("Opcao: ");
        op = lerOpcao();

        switch(op){

        case 1: {
            Professor p;
            char nome[TAM_NOME] = "", area[TAM_AREA] = "", email[TAM_EMAIL] = "";
            int mat = 0;

            printf("Matricula: ");
            scanf("%d", &mat);
            if(buscarP(&s->professores, mat) != -1){
                printf("Professor ja cadastrado.\n");
                break;
            }
            printf("Nome: ");
            scanf(" %99[^\n]", nome);
            printf("Area de atuacao: ");
            scanf(" %49[^\n]", area);
            printf("E-mail: ");
            scanf(" %99[^\n]", email);

            if(iniciarProfessor(&p, mat, nome, area, email) && inserirP(&s->professores, p)){
                printf("Professor cadastrado.\n");
            }
            break;
        }

        case 2: {
            int mat = 0;

            printf("Matricula: ");
            scanf("%d", &mat);
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
            int mat = 0, i;

            printf("Matricula: ");
            scanf("%d", &mat);
            i = buscarP(&s->professores, mat);
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
            char nome[TAM_NOME] = "", area[TAM_AREA] = "", email[TAM_EMAIL] = "";
            int mat = 0;

            printf("Matricula: ");
            scanf("%d", &mat);
            if(buscarP(&s->professores, mat) == -1){
                printf("Professor nao encontrado.\n");
                break;
            }
            printf("Novo nome: ");
            scanf(" %99[^\n]", nome);
            printf("Nova area de atuacao: ");
            scanf(" %49[^\n]", area);
            printf("Novo e-mail: ");
            scanf(" %99[^\n]", email);

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
        printf("Opcao: ");
        op = lerOpcao();

        switch(op){

        case 1: {
            char horario[TAM_HORARIO] = "", sala[TAM_SALA] = "";
            int cod = 0, disc = 0, prof = 0, vagas = 0;

            printf("Codigo da turma: ");
            scanf("%d", &cod);
            if(buscarTurma(&s->turmas, cod) != -1){
                printf("Turma ja cadastrada.\n");
                break;
            }
            printf("Codigo da disciplina: ");
            scanf("%d", &disc);
            printf("Matricula do professor: ");
            scanf("%d", &prof);
            printf("Horario (ex.: Seg 08:00-10:00): ");
            scanf(" %29[^\n]", horario);
            printf("Sala: ");
            scanf(" %19[^\n]", sala);
            printf("Numero de vagas: ");
            scanf("%d", &vagas);

            if(cadastrarTurma(&s->turmas, &s->disciplinas, &s->professores,
                              cod, disc, prof, horario, sala, vagas)){
                printf("Turma cadastrada.\n");
            }
            break;
        }

        case 2: {
            int cod = 0;

            printf("Codigo da turma: ");
            scanf("%d", &cod);
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
            int cod = 0, i;

            printf("Codigo da turma: ");
            scanf("%d", &cod);
            i = buscarTurma(&s->turmas, cod);
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
        printf("Opcao: ");
        op = lerOpcao();

        switch(op){

        case 1: {
            char semestre[TAM_SEMESTRE] = "";
            int mat = 0, turma = 0;

            printf("Matricula do aluno: ");
            scanf("%d", &mat);
            printf("Codigo da turma: ");
            scanf("%d", &turma);
            printf("Semestre (ex.: 2026.1): ");
            scanf(" %9[^\n]", semestre);

            if(matricularAluno(&s->matriculas, &s->alunos, &s->turmas, &s->disciplinas,
                               mat, turma, semestre)){
                printf("Aluno matriculado.\n");
            }
            break;
        }

        case 2: {
            int mat = 0, turma = 0;

            printf("Matricula do aluno: ");
            scanf("%d", &mat);
            printf("Codigo da turma: ");
            scanf("%d", &turma);

            if(cancelarMatricula(&s->matriculas, mat, turma)){
                printf("Matricula cancelada.\n");
            }
            break;
        }

        case 3: {
            int mat = 0, turma = 0;
            float nota = -1.0f;

            printf("Matricula do aluno: ");
            scanf("%d", &mat);
            printf("Codigo da turma: ");
            scanf("%d", &turma);
            printf("Nota (0 a 10, use ponto): ");
            scanf("%f", &nota);

            if(registrarNota(&s->matriculas, mat, turma, nota)){
                int i = buscarMatricula(&s->matriculas, mat, turma);
                printf("Nota registrada. Situacao: %s\n",
                       nomeSituacao(s->matriculas.dados[i].situacao));
            }
            break;
        }

        case 4: {
            int mat = 0, turma = 0;
            float freq = -1.0f;

            printf("Matricula do aluno: ");
            scanf("%d", &mat);
            printf("Codigo da turma: ");
            scanf("%d", &turma);
            printf("Frequencia (0 a 100, use ponto): ");
            scanf("%f", &freq);

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
        printf("Opcao: ");
        op = lerOpcao();

        switch(op){

        case 1: {
            int mat = 0;

            printf("Matricula do aluno: ");
            scanf("%d", &mat);
            if(entrarNaFila(&s->fila, &s->alunos, mat)){
                printf("Aluno inserido na fila (posicao %d).\n", s->fila.tamanho);
            }
            break;
        }

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
        printf("Opcao: ");
        op = lerOpcao();

        switch(op){

        case 1: {
            int mat = 0;

            printf("Matricula do aluno: ");
            scanf("%d", &mat);
            consultarSituacaoAcademica(&s->matriculas, &s->alunos, mat);
            break;
        }

        case 2: {
            int turma = 0;

            printf("Codigo da turma: ");
            scanf("%d", &turma);
            listarAlunosTurma(&s->matriculas, &s->alunos, &s->turmas, turma);
            break;
        }

        case 3: {
            int mat = 0;

            printf("Matricula do aluno: ");
            scanf("%d", &mat);
            listarDisciplinasAluno(&s->matriculas, &s->alunos, &s->turmas, &s->disciplinas, mat);
            break;
        }

        case 4: {
            int mat = 0;

            printf("Matricula do aluno: ");
            scanf("%d", &mat);
            historicoAcademico(&s->matriculas, &s->alunos, &s->turmas, &s->disciplinas, mat);
            break;
        }

        case 5: {
            int cod = 0;

            printf("Codigo da disciplina: ");
            scanf("%d", &cod);
            listarPrerequisitos(&s->disciplinas, cod);
            break;
        }

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
        printf("Opcao: ");
        op = lerOpcao();

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