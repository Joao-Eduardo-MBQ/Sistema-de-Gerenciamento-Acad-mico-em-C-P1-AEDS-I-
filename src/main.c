#include <stdio.h>
#include <string.h>
#include "../include/aluno.h"
#include "../include/professor.h"
#include "../include/turma.h"

/* ======================= MENU DE TURMAS ======================= */

void menuTurma(VetorTurmas *turmas, VetorAlunos *alunos, VetorProfessores *professores){
    Turma t;
    char  sala[TAM_SALA], materia[TAM_DISCIPLINA];
    int   op, nTurma, matricula, registro;

    do{
        printf("\n----- TURMAS -----\n");
        printf("1. Inserir\n");
        printf("2. Remover\n");
        printf("3. Buscar\n");
        printf("4. Listar\n");
        printf("5. Adicionar aluno\n");
        printf("6. Remover aluno\n");
        printf("7. Designar professor\n");
        printf("0. Voltar\n");
        printf("Opcao: ");

        if(scanf("%d", &op) != 1){
            int c;
            while((c = getchar()) != '\n' && c != EOF){ }
            op = -1;
        }

        switch(op){

        case 1:
            printf("Numero da turma: ");
            scanf("%d", &nTurma);
            if(buscarturma(turmas, nTurma) != -1){
                printf("Turma ja cadastrada.\n");
                break;
            }
            printf("Sala: ");
            scanf(" %19[^\n]", sala);
            printf("Materia: ");
            scanf(" %49[^\n]", materia);
            iniciarTurma(&t, nTurma, sala, materia);
            if(inserirTurma(turmas, t)){
                printf("Turma inserida.\n");
            }
            break;

        case 2:
            printf("Numero da turma: ");
            scanf("%d", &nTurma);
            if(removerTurma(turmas, nTurma)){
                printf("Turma removida.\n");
            } else {
                printf("Turma nao encontrada.\n");
            }
            break;

        case 3: {
            printf("Numero da turma: ");
            scanf("%d", &nTurma);
            int i = buscarturma(turmas, nTurma);
            if(i == -1){
                printf("Turma nao encontrada.\n");
            } else {
                imprimirTurma(&turmas->dados[i], professores);
            }
            break;
        }

        case 4:
            listarTurmas(turmas, professores);
            break;

        case 5:
            printf("Numero da turma: ");
            scanf("%d", &nTurma);
            printf("Matricula do aluno: ");
            scanf("%d", &matricula);
            if(buscarA(alunos, matricula) == -1){
                printf("Aluno nao cadastrado.\n");
            } else if(adicionarAlunoTurma(turmas, nTurma, matricula)){
                printf("Aluno adicionado a turma.\n");
            }
            break;

        case 6:
            printf("Numero da turma: ");
            scanf("%d", &nTurma);
            printf("Matricula do aluno: ");
            scanf("%d", &matricula);
            if(removerAlunoTurma(turmas, nTurma, matricula)){
                printf("Aluno removido da turma.\n");
            }
            break;

        case 7:
            printf("Numero da turma: ");
            scanf("%d", &nTurma);
            printf("Registro do professor: ");
            scanf("%d", &registro);
            if(buscarP(professores, registro) == -1){
                printf("Professor nao encontrado.\n");
            } else if(designarProfessorTurma(turmas, nTurma, registro)){
                printf("Professor designado.\n");
            }
            break;

        case 0:
            break;

        default:
            printf("Opcao invalida.\n");
        }
    } while(op != 0);
}

/* ======================= MENU DE ALUNOS ======================= */

void menuAluno(VetorAlunos *alunos){
    Aluno a;
    char  disc[TAM_DISCIPLINA];
    int   op, id, i, prova;
    float nota;

    do{
        printf("\n----- ALUNOS -----\n");
        printf("1. Inserir\n");
        printf("2. Remover\n");
        printf("3. Buscar\n");
        printf("4. Listar\n");
        printf("5. Editar\n");
        printf("6. Adicionar disciplina\n");
        printf("7. Remover disciplina\n");
        printf("8. Lancar nota\n");
        printf("0. Voltar\n");
        printf("Opcao: ");

        // se digitar letra em vez de numero, descarta a linha
        if(scanf("%d", &op) != 1){
            int c;
            while((c = getchar()) != '\n' && c != EOF){ }
            op = -1;
        }

        switch(op){

        case 1:
            memset(&a, 0, sizeof(a));
            printf("Matricula: ");
            scanf("%d", &a.matricula);
            if(buscarA(alunos, a.matricula) != -1){
                printf("Aluno ja cadastrado.\n");
                break;
            }
            printf("Nome: ");
            scanf(" %99[^\n]", a.nomeA);
            printf("Idade: ");
            scanf("%d", &a.idadeA);
            printf("Curso: ");
            scanf(" %49[^\n]", a.curso);
            a.qtdD = 0;

            inserirA(alunos, a);
            break;

        case 2:
            printf("Matricula: ");
            scanf("%d", &id);
            if(removerA(alunos, id)){
                printf("Aluno removido.\n");
            }
            else{
                printf("Aluno nao encontrado.\n");
            }
            break;

        case 3:
            printf("Matricula: ");
            scanf("%d", &id);
            i = buscarA(alunos, id);
            if(i == -1){
                printf("Aluno nao encontrado.\n");
            }
            else{
                Aluno *ap = &alunos->dados[i];
                printf("Posicao %d | %s | %d anos | %s | %d disciplinas\n",
                       i, ap->nomeA, ap->idadeA, ap->curso, ap->qtdD);
            }
            break;

        case 4:
            listarA(alunos);
            break;

        case 5:
            memset(&a, 0, sizeof(a));
            printf("Matricula: ");
            scanf("%d", &id);
            printf("Novo nome: ");
            scanf(" %99[^\n]", a.nomeA);
            printf("Nova idade: ");
            scanf("%d", &a.idadeA);
            printf("Novo curso: ");
            scanf(" %49[^\n]", a.curso);
            editarAluno(alunos, id, a.nomeA, a.idadeA, a.curso);
            break;

        case 6:
            printf("Matricula: ");
            scanf("%d", &id);
            printf("Disciplina: ");
            scanf(" %49[^\n]", disc);
            if(adicionarDisciplina(alunos, id, disc)){
                printf("Disciplina adicionada.\n");
            }
            break;

        case 7:
            printf("Matricula: ");
            scanf("%d", &id);
            printf("Disciplina: ");
            scanf(" %49[^\n]", disc);
            if(removerDisciplina(alunos, id, disc)){
                printf("Disciplina removida.\n");
            }
            break;

        case 8:
            printf("Matricula: ");
            scanf("%d", &id);
            printf("Disciplina: ");
            scanf(" %49[^\n]", disc);
            printf("Prova (1 a %d): ", MAX_PROVAS);
            scanf("%d", &prova);
            printf("Nota (0 a 10): ");
            scanf("%f", &nota);
            if(nota < 0 || nota > 10){
                printf("Nota invalida.\n");
            } else {
                lancarNota(alunos, id, disc, prova, nota);
            }
            break;

        case 0:
            break;

        default:
            printf("Opcao invalida.\n");
        }

    } while(op != 0);
}

/* ===================== MENU DE PROFESSORES ===================== */

void menuProfessor(VetorProfessores *professores){
    Professor p;
    char      disc[TAM_DISCIPLINA], horario[TAM_HORARIO];
    int       op, id, i;

    do{
        printf("\n----- PROFESSORES -----\n");
        printf("1. Inserir\n");
        printf("2. Remover\n");
        printf("3. Buscar\n");
        printf("4. Listar\n");
        printf("5. Editar\n");
        printf("6. Adicionar aula\n");
        printf("7. Remover aula\n");
        printf("0. Voltar\n");
        printf("Opcao: ");

        if(scanf("%d", &op) != 1){
            int c;
            while((c = getchar()) != '\n' && c != EOF){ }
            op = -1;
        }

        switch(op){

        case 1:
            memset(&p, 0, sizeof(p));
            printf("Registro: ");
            if(scanf("%d", &p.registro) != 1){
                printf("Erro: o registro deve ser um numero inteiro.\n");
                int c;
                while((c = getchar()) != '\n' && c != EOF){ }
                break;
            }

            if(buscarP(professores, p.registro) != -1){
                printf("Registro ja cadastrado.\n");
                break;
            }

            printf("Nome: ");
            scanf(" %99[^\n]", p.nomeP);

            if(inserirP(professores, p)){
                printf("Professor inserido com sucesso.\n");
            } else {
                printf("Erro ao inserir professor.\n");
            }
            break;

        case 2:
            printf("Registro: ");
            scanf("%d", &id);
            if(removerP(professores, id)){
                printf("Professor removido.\n");
            }
            else{
                printf("Professor nao encontrado.\n");
            }
            break;

        case 3:
            printf("Registro: ");
            scanf("%d", &id);
            i = buscarP(professores, id);
            if(i == -1){
                printf("Professor nao encontrado.\n");
            } else {
                printf("Posicao %d | %s | %d aulas\n", i,
                       professores->dados[i].nomeP, professores->dados[i].qtdAulas);
            }
            break;

        case 4:
            listarP(professores);
            break;

        case 5:
            memset(&p, 0, sizeof(p));
            printf("Registro: ");
            scanf("%d", &id);
            printf("Novo nome: ");
            scanf(" %99[^\n]", p.nomeP);
            editarProfessor(professores, id, p.nomeP);
            break;

        case 6:
            printf("Registro: ");
            scanf("%d", &id);
            printf("Disciplina: ");
            scanf(" %49[^\n]", disc);
            printf("Horario (ex.: Seg 08:00-10:00): ");
            scanf(" %29[^\n]", horario);
            if(adicionarAula(professores, id, disc, horario)){
                printf("Aula adicionada.\n");
            }
            break;

        case 7:
            printf("Registro: ");
            scanf("%d", &id);
            printf("Disciplina: ");
            scanf(" %49[^\n]", disc);
            if(removerAula(professores, id, disc)){
                printf("Aula removida.\n");
            }
            break;

        case 0:
            break;

        default:
            printf("Opcao invalida.\n");
        }

    } while(op != 0);
}

/* ============================ MAIN ============================ */

int main(void){
    static VetorAlunos      alunos;
    static VetorProfessores professores;
    static VetorTurmas      turmas;
    int op;

    iniciarA(&alunos);
    iniciarP(&professores);
    iniciarVetorTurmas(&turmas);

    do{
        printf("\n===== SISTEMA ACADEMICO =====\n");
        printf("1. Menu de alunos\n");
        printf("2. Menu de professores\n");
        printf("3. Menu de turmas\n");
        printf("0. Sair\n");
        printf("Opcao: ");

        if(scanf("%d", &op) != 1){
            int c;
            while((c = getchar()) != '\n' && c != EOF){ }
            op = -1;
        }

        switch(op){
        case 1:
            menuAluno(&alunos);
            break;
        case 2:
            menuProfessor(&professores);
            break;
        case 3:
            menuTurma(&turmas, &alunos, &professores);
            break;
        case 0:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opcao invalida.\n");
        }

    } while(op != 0);

    return 0;
}