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
static void mostrar_menu_principal(int hay_reporte)
{
    printf("\n");
    mostrar_linea('=', 64);
    printf("  MENU PRINCIPAL\n");
    mostrar_linea('=', 64);
    printf("  1. Configurar la mision\n");
    printf("  2. Simular la trayectoria (por turnos)\n");
    printf("  3. Ver reporte de la ultima simulacion\n",
           hay_reporte ? "" : " (no disponible)");
    printf("  0. Salir\n");
}

static void submenu_analisis(const Mision *m)
{
    int op = -1;
    while (op != 0) {
        printf("\n === ANALISIS FISICO ===\n");
        printf("1.a_ 1ra Ley de Newton\n");
        printf("2.b_ Energia cinetica inicial\n");
        printf("3.c_ Trabajo minimo por unidad de masa\n");
        printf("4.d_ Ida vs. regreso: combustible\n");
        printf("5_ Mostrar todos\n");
        printf("0_ Volver\n");
        if (leer_entero("Seleccione una opcion (0-5): ", 0, 5, &op) != ENTRADA_OK) {
            return;
        }
        if (op == 1 || op == 5) mostrar_analisis_a(m);
        if (op == 2 || op == 5) mostrar_analisis_b(m);
        if (op == 3 || op == 5) mostrar_analisis_c(m);
        if (op == 4 || op == 5) mostrar_analisis_d(m);
        if (op != 0) {
            pausar();
        }
    }
}
