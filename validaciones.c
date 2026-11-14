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
    if (feof(stdin)) {            /* ultima linea sin salto de linea */
        return 0;
    }
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta el excedente para no contaminar la proxima lectura */
    }
    return 1;
}
