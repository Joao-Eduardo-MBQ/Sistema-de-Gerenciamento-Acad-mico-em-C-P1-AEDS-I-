#include <stdio.h>
#include "../include/fila.h"

void iniciarFila(FilaAtendimento *f){
    if(f == NULL){
        printf("Erro: fila invalida.\n");
        return;
    }
    f->inicio = 0;
    f->tamanho = 0;
}

int filaVazia(const FilaAtendimento *f){
    return f == NULL || f->tamanho == 0;
}

int filaCheia(const FilaAtendimento *f){
    return f != NULL && f->tamanho >= MAX_FILA;
}

int filaContem(const FilaAtendimento *f, int matricula){
    if(f == NULL){
        return 0;
    }

    for(int i = 0; i < f->tamanho; i++){
        if(f->dados[(f->inicio + i) % MAX_FILA] == matricula){
            return 1;
        }
    }
    return 0;
}

int entrarNaFila(FilaAtendimento *f, const VetorAlunos *va, int matricula){
    if(f == NULL || va == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    if(buscarA(va, matricula) == -1){
        printf("Aluno nao encontrado.\n");
        return 0;
    }

    if(filaContem(f, matricula)){
        printf("O aluno ja esta na fila.\n");
        return 0;
    }

    if(filaCheia(f)){
        printf("Fila de atendimento cheia.\n");
        return 0;
    }

    f->dados[(f->inicio + f->tamanho) % MAX_FILA] = matricula;
    f->tamanho++;
    return 1;
}

int atenderProximo(FilaAtendimento *f, const VetorAlunos *va){
    if(f == NULL || va == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    if(filaVazia(f)){
        printf("Nao ha ninguem na fila.\n");
        return 0;
    }

    int mat = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->tamanho--;

    int a = buscarA(va, mat);
    printf("Atendendo: %s (matricula %d)\n", a != -1 ? va->dados[a].nome : "(removido)", mat);
    return 1;
}

void proximoDaFila(const FilaAtendimento *f, const VetorAlunos *va){
    if(f == NULL || va == NULL){
        printf("Erro: dados invalidos.\n");
        return;
    }

    if(filaVazia(f)){
        printf("Nao ha ninguem na fila.\n");
        return;
    }

    int mat = f->dados[f->inicio];
    int a = buscarA(va, mat);
    printf("Proximo: %s (matricula %d)\n", a != -1 ? va->dados[a].nome : "(removido)", mat);
}

void listarFila(const FilaAtendimento *f, const VetorAlunos *va){
    if(f == NULL || va == NULL){
        printf("Erro: dados invalidos.\n");
        return;
    }

    if(filaVazia(f)){
        printf("Fila vazia.\n");
        return;
    }

    printf("\nFila de atendimento (%d):\n", f->tamanho);
    for(int i = 0; i < f->tamanho; i++){
        int mat = f->dados[(f->inicio + i) % MAX_FILA];
        int a = buscarA(va, mat);
        printf("  %d. %s (matricula %d)\n", i + 1,
               a != -1 ? va->dados[a].nome : "(removido)", mat);
    }
}