/*
 * main.c - Menus del simulador (presentacion y principal).
 * Problema 3: Inyeccion Translunar (TLI) - Mision Artemis - 5 pilotos.
 */
#include <stdio.h>

#include "artemis.h"
#include "validaciones.h"

/* Menu de presentacion. Devuelve 1 si el usuario quiere jugar, 0 si sale. */
static int menu_presentacion(void)
{
    int op = -1;

    while (op != 0 && op != 1) {
        mostrar_logo();
        printf("  1. Comenzar\n");
        printf("  2. Historia de la mision\n");
        printf("  3. Reglas del juego\n");
        printf("  4. Creditos\n");
        printf("  0. Salir\n");
        if (leer_entero("Seleccione una opcion (0-4): ", 0, 4, &op) != ENTRADA_OK) {
            return 0;
        }
        if (op == 2) {
            mostrar_historia();
            pausar();
        } else if (op == 3) {
            mostrar_reglas();
            pausar();
        } else if (op == 4) {
            mostrar_creditos();
            pausar();
        }
    }
    return op;
}

static void mostrar_menu_principal(int registrados, int hay_resultado)
{
    printf("\n");
    mostrar_linea('=', 64);
    printf("  MENU PRINCIPAL\n");
    mostrar_linea('=', 64);
    printf("  1. Configurar parametros de la mision\n");
    printf("  2. Registrar los %d pilotos%s\n", NUM_PILOTOS,
           registrados ? " (ya registrados)" : "");
    printf("  3. Iniciar la competencia por turnos\n");
    printf("  4. Ver ranking y reportes%s\n",
           hay_resultado ? "" : " (no disponible)");
    printf("  0. Salir\n");
}

static void configurar_mision(Mision *m)
{
    Mision tmp;
    int op;

    mostrar_mision(m);
    printf("\n  1. Restaurar valores del enunciado\n");
    printf("  2. Ingresar valores nuevos\n");
    printf("  0. Volver\n");
    if (leer_entero("Seleccione una opcion (0-2): ", 0, 2, &op) != ENTRADA_OK) {
        return;
    }
    if (op == 1) {
        mision_por_defecto(m);
        mostrar_aviso("Valores del enunciado restaurados.");
    } else if (op == 2) {
        if (leer_doble("Masa de Orion en kg (1000 - 1000000): ",
                       MIN_MASA, MAX_MASA, &tmp.masa) != ENTRADA_OK
            || leer_doble("Altura de la orbita LEO en m (160000 - 2000000): ",
                          MIN_ALTURA, MAX_ALTURA, &tmp.altura_leo) != ENTRADA_OK
            || leer_doble("Distancia Tierra-Luna en m (356000000 - 407000000): ",
                          MIN_DIST_TL, MAX_DIST_TL, &tmp.dist_tierra_luna) != ENTRADA_OK) {
            return;
        }
        *m = tmp;
        mostrar_aviso("Parametros actualizados.");
        mostrar_mision(m);
    }
}

static void menu_resultados(const Mision *m, const Piloto pilotos[])
{
    int op = -1, n;

    while (op != 0) {
        printf("\n  --- RANKING Y REPORTES ---\n");
        printf("  1. Ver ranking final\n");
        printf("  2. Ver reporte de un piloto\n");
        printf("  0. Volver\n");
        if (leer_entero("Seleccione una opcion (0-2): ", 0, 2, &op) != ENTRADA_OK) {
            return;
        }
        if (op == 1) {
            mostrar_ranking(m, pilotos);
            pausar();
        } else if (op == 2) {
            mostrar_pilotos(pilotos);
            if (leer_entero("Numero de piloto (1-5): ", 1, NUM_PILOTOS, &n) != ENTRADA_OK) {
                return;
            }
            mostrar_reporte_piloto(m, &pilotos[n - 1]);
            pausar();
        }
    }
}

int main(void)
{
    Mision mision;
    Piloto pilotos[NUM_PILOTOS];
    int registrados = 0;
    int hay_resultado = 0;
    int opcion = -1;
    int estado;

    mision_por_defecto(&mision);

    if (!menu_presentacion()) {
        printf("\nHasta la proxima mision.\n");
        return 0;
    }

    while (opcion != 0) {
        mostrar_menu_principal(registrados, hay_resultado);
        if (leer_entero("Seleccione una opcion (0-4): ", 0, 4, &opcion) != ENTRADA_OK) {
            printf("\nFin de la entrada. Cerrando el simulador.\n");
            break;
        }
        switch (opcion) {
        case 1:
            configurar_mision(&mision);
            hay_resultado = 0;          /* los resultados anteriores ya no aplican */
            break;
        case 2:
            estado = registrar_pilotos(pilotos);
            if (estado == ENTRADA_OK) {
                registrados = 1;
                hay_resultado = 0;
            } else if (estado == ENTRADA_EOF) {
                opcion = 0;
            }
            break;
        case 3:
            if (!registrados) {
                mostrar_error("Primero debe registrar los pilotos (opcion 2).");
            } else {
                estado = ejecutar_competencia(&mision, pilotos);
                hay_resultado = 1;
                if (estado == ENTRADA_EOF) {
                    opcion = 0;
                } else {
                    pausar();
                }
            }
            break;
        case 4:
            if (hay_resultado) {
                menu_resultados(&mision, pilotos);
            } else {
                mostrar_error("Todavia no se ejecuto ninguna competencia.");
            }
            break;
        default:
            break;
        }
    }
    printf("\nHasta la proxima mision.\n");
    return 0;
}
