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
