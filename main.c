#include <stdio.h>

#include "artemis.h"
#include "validaciones.h"

/* Devuelve 1 si el usuario quiere comenzar, 0 si sale. */
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
        } else if (op == 3) {
            mostrar_reglas();
        } else if (op == 4) {
            mostrar_creditos();
        }
        if (op >= 2) {
            pausar();
        }
    }
    return op;
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
            || leer_doble("Velocidad de inyeccion en m/s (7000 - 15000): ",
                          MIN_V_TLI, MAX_V_TLI, &tmp.v_tli) != ENTRADA_OK
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

int main(void)
{
    Mision mision;
    Reporte reporte;
    int hay_reporte = 0;
    int opcion = -1;

    mision_por_defecto(&mision);

    if (!menu_presentacion()) {
        printf("\nHasta la proxima mision.\n");
        return 0;
    }

    while (opcion != 0) {
        printf("\n");
        mostrar_linea('=', 64);
        printf("  MENU PRINCIPAL\n");
        mostrar_linea('=', 64);
        printf("  1. Configurar parametros de la mision\n");
        printf("  2. Simular la trayectoria translunar (por turnos)\n");
        printf("  3. Ver reporte de la ultima simulacion%s\n",
               hay_reporte ? "" : " (no disponible)");
        printf("  0. Salir\n");
        if (leer_entero("Seleccione una opcion (0-3): ", 0, 3, &opcion) != ENTRADA_OK) {
            printf("\nFin de la entrada. Cerrando el simulador.\n");
            break;
        }
        switch (opcion) {
        case 1:
            configurar_mision(&mision);
            break;
        case 2:
            ejecutar_simulacion(&mision, &reporte);
            hay_reporte = 1;
            pausar();
            break;
        case 3:
            if (hay_reporte) {
                mostrar_reporte(&mision, &reporte);
                pausar();
            } else {
                mostrar_error("Todavia no ejecuto ninguna simulacion.");
            }
            break;
        default:
            break;
        }
    }
    printf("\nHasta la proxima mision.\n");
    return 0;
}
