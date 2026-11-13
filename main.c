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
