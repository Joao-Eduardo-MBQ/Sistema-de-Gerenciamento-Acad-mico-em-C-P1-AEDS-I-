#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "../include/util.h"

void copiarStr(char *dest, size_t tam, const char *src){
    if(dest == NULL || tam == 0){
        return;
    }
    if(src == NULL){
        dest[0] = '\0';
        return;
    }
    strncpy(dest, src, tam - 1);
    dest[tam - 1] = '\0';
}

int emailValido(const char *email){
    if(email == NULL){
        return 0;
    }

    const char *arroba = strchr(email, '@');
    if(arroba == NULL || arroba == email){
        return 0;
    }

    const char *ponto = strchr(arroba, '.');
    if(ponto == NULL || ponto == arroba + 1 || *(ponto + 1) == '\0'){
        return 0;
    }

    return strchr(email, ' ') == NULL;
}

/* le uma linha inteira; descarta o excesso se passar do tamanho */
static int lerLinha(char *buf, int tam){
    if(fgets(buf, tam, stdin) == NULL){
        return 0;
    }

    size_t n = strlen(buf);
    if(n > 0 && buf[n - 1] == '\n'){
        buf[n - 1] = '\0';
    } else {
        int c;
        while((c = getchar()) != '\n' && c != EOF){ }
    }
    return 1;
}

void lerString(const char *prompt, char *dest, int tam){
    while(1){
        printf("%s", prompt);
        if(!lerLinha(dest, tam)){
            dest[0] = '\0';         /* EOF */
            return;
        }
        if(dest[0] != '\0'){
            return;
        }
        printf("Campo obrigatorio.\n");
    }
}

int lerInt(const char *prompt){
    char buf[64];

    while(1){
        printf("%s", prompt);
        if(!lerLinha(buf, sizeof(buf))){
            return 0;               /* EOF: faz os menus encerrarem */
        }

        char *fim;
        long v = strtol(buf, &fim, 10);
        int ok = (fim != buf);
        while(isspace((unsigned char)*fim)){
            fim++;
        }

        if(ok && *fim == '\0' && v >= INT_MIN && v <= INT_MAX){
            return (int)v;
        }
        printf("Valor invalido. Digite um numero inteiro.\n");
    }
}

float lerFloat(const char *prompt){
    char buf[64];

    while(1){
        printf("%s", prompt);
        if(!lerLinha(buf, sizeof(buf))){
            return 0.0f;
        }

        for(char *c = buf; *c; c++){
            if(*c == ','){
                *c = '.';           /* aceita 7,5 */
            }
        }

        char *fim;
        double v = strtod(buf, &fim);
        int ok = (fim != buf);
        while(isspace((unsigned char)*fim)){
            fim++;
        }

        if(ok && *fim == '\0'){
            return (float)v;
        }
        printf("Valor invalido. Digite um numero (ex.: 7.5).\n");
    }
}