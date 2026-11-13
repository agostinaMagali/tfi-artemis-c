void mostrar_analisis_a(const Mision *m) {
  printf("\n==== 1ra Ley de Newton ====\n");
  printf("Con los motores apagados, la nave no se detiene.\n");
  printf("Conserva su movimiento por inercia y se aleja de la Tierra, \n");
  printf("frenando de a poco debido a la fuerza de gravedad.\n");
}

void mostrar_analisis_b(const Mision *m) {
  //Fórmula: K = 0.5 * masa * velocidad al cuadrado
  double ki = 0.5 * m->masa * m->v_tli * m->v_tli;
  printf("\n==== Energia Cinetica Inicial ====\n");
  printf("Masa de Orion: %.1f kg\n", m->masa);
  printf("Velocidad de inyección: %.1f m/s\n", m->v_tli);
  printf("Energia Cinetica: %.4e Joules (J)\n", ki);
}

void mostrar_analisis_c(const Mision *m) {
    double adicional = trabajo_adicional_por_masa(m);
    double v_min = velocidad_minima_tli(m);
    printf("\n==== Conservacion de la energia mecanica ====\n");
    printf("  Trabajo ADICIONAL minimo .... %.4e J/kg\n", adicional);
    if (adicional > 0.0) {
        printf("Con v = %.1f m/s Orion no alcanza el equilibrio por inercia.\n", m->v_tli);
    } else {
        printf("La energia de la TLI ya alcanza: no se requiere trabajo adicional.\n");
    }
    printf("Velocidad minima de inyeccion necesaria: %.2f m/s\n", v_min);
}

void mostrar_analisis_d(const Mision *m) {
    double r1 = radio_orbital(m);
    double dv_ida = m->v_tli - velocidad_circular(GM_TIERRA, r1);
    if (dv_ida < 0.0) dv_ida = 0.0;
    double mp_ida = masa_propelente(m->masa, dv_ida, VEL_GASES);
    printf("\n==== Combustible: Ida vs. Vuelta ====\n");
    printf("Propelente necesario para la Ida (LEO -> TLI): %.1f kg\n", mp_ida);
    printf("Justificacion: La Tierra tiene un pozo gravitacional mucho mas profundo\n");
    printf("que la Luna, por lo que salir de ella requiere un gasto exponencial mayor.\n");
}
