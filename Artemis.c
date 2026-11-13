void mision_por_defecto(Mision *m) {
    m->masa = DEF_MASA;
    m->v_tli = DEF_V_TLI;
    m->altura_leo = DEF_ALTURA;
    m->dist_tierra_luna = DEF_DIST_TL;
}

double radio_orbital(const Mision *m) {
  return RADIO_TIERRA + m->altura_leo;
}

double energia_cinetica(double masa, double v) {
    return 0.5 * masa * v * v;
}

double potencial_especifico(double r, double dist_tl) {
    return -GM_TIERRA / r - GM_LUNA / (dist_tl - r);
}

double aceleracion_radial(double r, double dist_tl) {
    double dl = dist_tl - r;
    return -GM_TIERRA / (r * r) + GM_LUNA / (dl * dl);
}

double radio_equilibrio(double dist_tl) {
    return dist_tl / (1.0 + sqrt(MASA_LUNA / MASA_TIERRA));
}

double trabajo_por_masa_total(const Mision *m) {
    double d = m->dist_tierra_luna;
    return potencial_especifico(radio_equilibrio(d), d) - potencial_especifico(radio_orbital(m), d);
}

double trabajo_adicional_por_masa(const Mision *m) {
    double faltante = trabajo_por_masa_total(m) - 0.5 * m->v_tli * m->v_tli;
    return (faltante > 0.0) ? faltante : 0.0;
}

double velocidad_minima_tli(const Mision *m) {
    return sqrt(2.0 * trabajo_por_masa_total(m));
}

double velocidad_circular(double gm, double r) {
    return sqrt(gm / r);
}

double velocidad_escape(double gm, double r) {
    return sqrt(2.0 * gm / r);
}

double masa_propelente(double masa_final, double delta_v, double v_gases) {
    return masa_final * (exp(delta_v / v_gases) - 1.0);
}

void mostrar_analisis_a(const Mision *m) {
  double d = m->dist_tierra_luna;
  double r1 = radio_orbital(m);
  double r[6];
  const double *pr = r;
  const double km[4] = {20000.0, 50000.0, 100000.0, 200000.0};
  double a, v2;
  int i;
  r[0] = r1;
  for (i = 0; i < 4; i++) {
      r[i + 1] = km[i] * 1000.0;
  }
  r[5] = radio_equilibrio(d);
  printf("\n==== 1ra Ley de Newton ====\n");
  printf("Con los motores apagados, la nave no se detiene.\n");
  printf("Conserva su movimiento por inercia y se aleja de la Tierra, \n");
  printf("frenando de a poco debido a la fuerza de gravedad.\n");
  printf("Distancia (km) | Aceleracion (m/s^2) | Velocidad (m/s)\n");
  for (i = 0; i < 6; i++) {
      a = aceleracion_radial(pr[i], d);
      v2 = m->v_tli * m->v_tli - 2.0 * (potencial_especifico(pr[i], d) - potencial_especifico(r1, d));
      printf("%14.1f | %19.5f | ", pr[i] / 1000.0, a);
      if (v2 > 0.0) {
          printf("%15.2f\n", sqrt(v2));
      } else {
          printf("   no alcanza\n");
      }
  }
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
  printf("  Trabajo adicional minimo .... %.4e J/kg\n", adicional);
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
