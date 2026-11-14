#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validaciones.h"

int leer_linea(char *buf, size_t n)
{
    size_t len;
    int c;
    if (fgets(buf, (int)n, stdin) == NULL) {
        return ENTRADA_EOF;
    }
    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
        return 0;
    }
    if (feof(stdin)) {           
        return 0;
    }
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    return 1;
}
static char *recortar(char *s)
{
    char *fin;

    while (*s != '\0' && isspace((unsigned char)*s)) {
        s++;
    }
    fin = s + strlen(s);
    while (fin > s && isspace((unsigned char)*(fin - 1))) {
        fin--;
    }
    *fin = '\0';
    return s;
}
int leer_entero(const char *msg, int min, int max, int *out)
{
    char buf[LONG_BUFFER];
    char texto[160];
    char *s, *fin;
    long valor;
    int r;
    for (;;) {
        printf("%s", msg);
        fflush(stdout);
        r = leer_linea(buf, sizeof buf);
        if (r == ENTRADA_EOF) {
            return ENTRADA_EOF;
        }
        if (r == 1) {
            mostrar_error("La entrada es demasiado larga.");
            continue;
        }
        s = recortar(buf);
        if (*s == '\0') {
            mostrar_error("No ingreso ningun valor.");
            continue;
        }
        errno = 0;
        valor = strtol(s, &fin, 10);
        if (fin == s || *fin != '\0') {
            mostrar_error("Debe ingresar un numero entero (sin letras, simbolos ni decimales).");
            continue;
        }
        if (errno == ERANGE || valor < min || valor > max) {
            snprintf(texto, sizeof texto,
                     "Valor fuera de rango. Debe estar entre %d y %d.", min, max);
            mostrar_error(texto);
            continue;
        }
        *out = (int)valor;
        return ENTRADA_OK;
    }
}

int leer_doble(const char *msg, double min, double max, double *out)
{
    char buf[LONG_BUFFER];
    char texto[200];
    char *s, *fin, *p;
    double valor;
    int r, comas, puntos, valido;
    for (;;) {
        printf("%s", msg);
        fflush(stdout);
        r = leer_linea(buf, sizeof buf);
        if (r == ENTRADA_EOF) {
            return ENTRADA_EOF;
        }
        if (r == 1) {
            mostrar_error("La entrada es demasiado larga.");
            continue;
        }
        s = recortar(buf);
        if (*s == '\0') {
            mostrar_error("No ingreso ningun valor.");
            continue;
        }
        valido = 1;
        comas = 0;
        puntos = 0;
        for (p = s; *p != '\0'; p++) {
            if (*p == ',') {
                comas++;
            } else if (*p == '.') {
                puntos++;
            } else if (!isdigit((unsigned char)*p) && *p != '+' && *p != '-'
                       && *p != 'e' && *p != 'E') {
                valido = 0;
            }
        }
        if (!valido || comas + puntos > 1) {
            mostrar_error("Debe ingresar un numero real valido (ej.: 10900 o 10900,5).");
            continue;
        }
        for (p = s; *p != '\0'; p++) {   /* acepta coma decimal (uso local) */
            if (*p == ',') {
                *p = '.';
            }
        }
        errno = 0;
        valor = strtod(s, &fin);
        if (fin == s || *fin != '\0' || !isfinite(valor)) {
            mostrar_error("Debe ingresar un numero real valido (ej.: 10900 o 10900,5).");
            continue;
        }
        if (errno == ERANGE || valor < min || valor > max) {
            snprintf(texto, sizeof texto,
                     "Valor fuera de rango. Debe estar entre %.10g y %.10g.", min, max);
            mostrar_error(texto);
            continue;
        }
        *out = valor;
        return ENTRADA_OK;
    }
}

int leer_si_no(const char *msg, int *out)
{
    char buf[LONG_BUFFER];
    char *s;
    int r;

    for (;;) {
        printf("%s", msg);
        fflush(stdout);
        r = leer_linea(buf, sizeof buf);
        if (r == ENTRADA_EOF) {
            return ENTRADA_EOF;
        }
        if (r == 1) {
            mostrar_error("La entrada es demasiado larga.");
            continue;
        }
        s = recortar(buf);
        if (strcmp(s, "s") == 0 || strcmp(s, "S") == 0
            || strcmp(s, "si") == 0 || strcmp(s, "SI") == 0 || strcmp(s, "Si") == 0) {
            *out = 1;
            return ENTRADA_OK;
        }
        if (strcmp(s, "n") == 0 || strcmp(s, "N") == 0
            || strcmp(s, "no") == 0 || strcmp(s, "NO") == 0 || strcmp(s, "No") == 0) {
            *out = 0;
            return ENTRADA_OK;
        }
        mostrar_error("Responda con 's' (si) o 'n' (no).");
    }
}

void mostrar_error(const char *texto)
{
    printf("  [ERROR] %s\n", texto);
}
void mostrar_aviso(const char *texto)
{
    printf("  [AVISO] %s\n", texto);
}
void mostrar_linea(char c, int cantidad)
{
    int i;

    for (i = 0; i < cantidad; i++) {
        putchar(c);
    }
    putchar('\n');
}

void pausar(void)
{
    char buf[LONG_BUFFER];

    printf("\nPresione Enter para continuar...");
    fflush(stdout);
    leer_linea(buf, sizeof buf);
}
