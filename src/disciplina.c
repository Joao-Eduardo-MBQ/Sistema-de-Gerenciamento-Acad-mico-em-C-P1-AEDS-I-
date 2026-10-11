#include <stdio.h>
#include <string.h>
#include "../include/disciplina.h"

void iniciarVetorDisciplinas(VetorDisciplinas *vd){
    if(vd == NULL){
        printf("Erro: vetor invalido.\n");
        return;
    }
    vd->tamanho = 0;
}

int iniciarDisciplina(Disciplina *d, int codigo, const char *nome, int cargaHoraria, const char *periodo, int vagas){
    if(d == NULL || nome == NULL || periodo == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    if(codigo <= 0){
        printf("Codigo invalido.\n");
        return 0;
    }

    if(cargaHoraria <= 0){
        printf("Carga horaria invalida.\n");
        return 0;
    }

    if(vagas < 0){
        printf("Numero de vagas invalido.\n");
        return 0;
    }

    memset(d, 0, sizeof(*d));
    d->codigo = codigo;
    strncpy(d->nome, nome, sizeof(d->nome) - 1);
    d->nome[sizeof(d->nome) - 1] = '\0';
    d->cargaHoraria = cargaHoraria;
    strncpy(d->periodo, periodo, sizeof(d->periodo) - 1);
    d->periodo[sizeof(d->periodo) - 1] = '\0';
    d->vagas = vagas;
    d->qtdPrereq = 0;
    return 1;
}

int buscarDisciplina(const VetorDisciplinas *vd, int codigo){
    if(vd == NULL){
        return -1;
    }

    for(int i = 0; i < vd->tamanho; i++){
        if(vd->dados[i].codigo == codigo){
            return i;
        }
    }
    return -1;
}

int inserirDisciplina(VetorDisciplinas *vd, Disciplina d){
    if(vd == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    if(vd->tamanho >= MAX_DISCIPLINAS){
        printf("Vetor de disciplinas cheio.\n");
        return 0;
    }

    if(buscarDisciplina(vd, d.codigo) != -1){
        printf("Codigo ja cadastrado.\n");
        return 0;
    }

    vd->dados[vd->tamanho] = d;
    vd->tamanho++;
    return 1;
}

int disciplinaEhPrerequisito(const VetorDisciplinas *vd, int codigo){
    if(vd == NULL){
        return 0;
    }

    for(int i = 0; i < vd->tamanho; i++){
        for(int k = 0; k < vd->dados[i].qtdPrereq; k++){
            if(vd->dados[i].prerequisitos[k] == codigo){
                return 1;
            }
        }
    }
    return 0;
}

int removerDisciplina(VetorDisciplinas *vd, int codigo){
    if(vd == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    int i = buscarDisciplina(vd, codigo);
    if(i == -1){
        printf("Disciplina nao encontrada.\n");
        return 0;
    }

    if(disciplinaEhPrerequisito(vd, codigo)){
        printf("Nao e possivel remover: a disciplina e pre-requisito de outra.\n");
        return 0;
    }

    for(int j = i; j < vd->tamanho - 1; j++){
        vd->dados[j] = vd->dados[j + 1];
    }
    vd->tamanho--;
    return 1;
}

int editarDisciplina(VetorDisciplinas *vd, int codigo, const char *nome, int cargaHoraria, const char *periodo, int vagas){
    if(vd == NULL || nome == NULL || periodo == NULL){
        printf("Erro: dados invalidos.\n");
        return 0;
    }

    int i = buscarDisciplina(vd, codigo);
    if(i == -1){
        printf("Disciplina nao encontrada.\n");
        return 0;
    }

    if(cargaHoraria <= 0){
        printf("Carga horaria invalida.\n");
        return 0;
    }

    if(vagas < 0){
        printf("Numero de vagas invalido.\n");
        return 0;
    }

    Disciplina *d = &vd->dados[i];
    strncpy(d->nome, nome, sizeof(d->nome) - 1);
    d->nome[sizeof(d->nome) - 1] = '\0';
    strncpy(d->periodo, periodo, sizeof(d->periodo) - 1);
    d->periodo[sizeof(d->periodo) - 1] = '\0';
    d->cargaHoraria = cargaHoraria;
    d->vagas = vagas;
    return 1;
}

void imprimirDisciplina(const Disciplina *d){
    printf("Codigo %d | %s | %dh | Periodo: %s | Vagas: %d | Pre-req: ",
           d->codigo, d->nome, d->cargaHoraria, d->periodo, d->vagas);

    if(d->qtdPrereq == 0){
        printf("-");
    }
    for(int k = 0; k < d->qtdPrereq; k++){
        printf("%s%d", k ? ", " : "", d->prerequisitos[k]);
    }
    printf("\n");
}

void listarDisciplinas(const VetorDisciplinas *vd){
    if(vd == NULL){
        printf("Erro: vetor invalido.\n");
        return;
    }

    if(vd->tamanho == 0){
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }

    for(int i = 0; i < vd->tamanho; i++){
        imprimirDisciplina(&vd->dados[i]);
    }
}

/* ------------------------- pre-requisitos ------------------------- */

static int dependeDe(const VetorDisciplinas *vd, int a, int b){
    int i = buscarDisciplina(vd, a);
    if(i == -1){
        return 0;
    }

    const Disciplina *d = &vd->dados[i];
    for(int k = 0; k < d->qtdPrereq; k++){
        if(d->prerequisitos[k] == b || dependeDe(vd, d->prerequisitos[k], b)){
            return 1;
        }
    }
    return 0;
}

int adicionarPrerequisito(VetorDisciplinas *vd, int codigo, int codPrereq){
    if(vd == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    int i = buscarDisciplina(vd, codigo);
    if(i == -1){
        printf("Disciplina %d nao encontrada.\n", codigo);
        return 0;
    }

    if(buscarDisciplina(vd, codPrereq) == -1){
        printf("Disciplina %d (pre-requisito) nao encontrada.\n", codPrereq);
        return 0;
    }

    if(codigo == codPrereq){
        printf("Uma disciplina nao pode ser pre-requisito de si mesma.\n");
        return 0;
    }

    Disciplina *d = &vd->dados[i];

    if(d->qtdPrereq >= MAX_PREREQ){
        printf("Limite de pre-requisitos atingido.\n");
        return 0;
    }

    for(int k = 0; k < d->qtdPrereq; k++){
        if(d->prerequisitos[k] == codPrereq){
            printf("Pre-requisito ja cadastrado.\n");
            return 0;
        }
    }

    if(dependeDe(vd, codPrereq, codigo)){
        printf("Pre-requisito invalido: criaria uma dependencia circular.\n");
        return 0;
    }

    d->prerequisitos[d->qtdPrereq] = codPrereq;
    d->qtdPrereq++;
    return 1;
}

int removerPrerequisito(VetorDisciplinas *vd, int codigo, int codPrereq){
    if(vd == NULL){
        printf("Erro: vetor invalido.\n");
        return 0;
    }

    int i = buscarDisciplina(vd, codigo);
    if(i == -1){
        printf("Disciplina %d nao encontrada.\n", codigo);
        return 0;
    }

    Disciplina *d = &vd->dados[i];
    for(int k = 0; k < d->qtdPrereq; k++){
        if(d->prerequisitos[k] == codPrereq){
            for(int z = k; z < d->qtdPrereq - 1; z++){
                d->prerequisitos[z] = d->prerequisitos[z + 1];
            }
            d->qtdPrereq--;
            return 1;
        }
    }

    printf("Esse pre-requisito nao existe para a disciplina.\n");
    return 0;
}

void listarPrerequisitos(const VetorDisciplinas *vd, int codigo){
    if(vd == NULL){
        printf("Erro: vetor invalido.\n");
        return;
    }

    int i = buscarDisciplina(vd, codigo);
    if(i == -1){
        printf("Disciplina nao encontrada.\n");
        return;
    }

    const Disciplina *d = &vd->dados[i];
    printf("Pre-requisitos de %d - %s:\n", d->codigo, d->nome);

    if(d->qtdPrereq == 0){
        printf("  (nenhum)\n");
        return;
    }

    for(int k = 0; k < d->qtdPrereq; k++){
        int p = buscarDisciplina(vd, d->prerequisitos[k]);
        printf("  %d - %s\n", d->prerequisitos[k], p != -1 ? vd->dados[p].nome : "(removida)");
    }
}