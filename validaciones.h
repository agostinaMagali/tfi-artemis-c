/*
 * validaciones.h - Ingreso seguro de datos y mensajes de interfaz.
 * Simulador de Misiones Artemis - Problema 3: Inyeccion Translunar (TLI)
 */
#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <stddef.h>

#define LONG_BUFFER 128

/* Codigos de retorno de las funciones de lectura */
#define ENTRADA_OK   0
#define ENTRADA_EOF -1   /* fin de entrada (Ctrl+D / Ctrl+Z): el programa debe terminar */

/* Lee una linea completa de stdin. Devuelve 0 si ok, 1 si la linea fue
   demasiado larga (se descarta el resto), -1 si hay EOF. */
int leer_linea(char *buf, size_t n);

/* Los tres lectores repiten la consulta hasta obtener un valor valido.
   Solo devuelven ENTRADA_OK o ENTRADA_EOF. */
int leer_entero(const char *msg, int min, int max, int *out);
int leer_doble(const char *msg, double min, double max, double *out);
int leer_si_no(const char *msg, int *out);   /* out = 1 (si) / 0 (no) */

/* Mensajes de interfaz */
void mostrar_error(const char *texto);
void mostrar_aviso(const char *texto);
void mostrar_linea(char c, int cantidad);
void pausar(void);

#endif
