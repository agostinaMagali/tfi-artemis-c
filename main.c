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
