#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stddef.h>

/* ---------- tamanhos de texto ---------- */
#define TAM_NOME        100
#define TAM_CURSO       50
#define TAM_EMAIL       100
#define TAM_AREA        50
#define TAM_DISCIPLINA  50
#define TAM_PERIODO     10      /* ex.: "2026.1" */
#define TAM_SEMESTRE    10      /* ex.: "2026.1" */
#define TAM_HORARIO     30      /* ex.: "Seg 08:00-10:00" */
#define TAM_SALA        20

/* ---------- capacidades ---------- */
#define MAX_ALUNO        100
#define MAX_PROFESSOR    100
#define MAX_DISCIPLINAS  100
#define MAX_PREREQ       5      /* pre-requisitos por disciplina */
#define MAX_TURMAS       50
#define MAX_MATRICULAS   1000
#define MAX_FILA         50

/* ---------- regras de aprovacao ---------- */
#define NOTA_MINIMA      6.0f   /* nota >= 6.0 */
#define FREQ_MINIMA      75.0f  /* frequencia >= 75% */

/* ---------- funcoes auxiliares ---------- */
void  copiarStr(char *dest, size_t tam, const char *src);
int   emailValido(const char *email);

/* leitura segura do teclado (nao deixam lixo no buffer) */
void  lerString(const char *prompt, char *dest, int tam);
int   lerInt(const char *prompt);
float lerFloat(const char *prompt);

#endif