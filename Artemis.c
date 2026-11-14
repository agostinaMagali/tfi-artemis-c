
#include <math.h>
#include <stdio.h>

#include "artemis.h"
#include "validaciones.h"



void mision_por_defecto(Mision *m)
{
    m->masa = DEF_MASA;
    m->v_tli = DEF_V_TLI;
    m->altura_leo = DEF_ALTURA;
    m->dist_tierra_luna = DEF_DIST_TL;
}

double radio_orbital(const Mision *m)
{
    return RADIO_TIERRA + m->altura_leo;
}

double energia_cinetica(double masa, double v)
{
    return 0.5 * masa * v * v;
}

/* Energia potencial por unidad de masa (Tierra + Luna) en la posicion r */
double potencial_especifico(double r, double dist_tl)
{
    return -GM_TIERRA / r - GM_LUNA / (dist_tl - r);
}

/* Aceleracion neta sobre la recta Tierra-Luna (positiva = hacia la Luna) */
double aceleracion_radial(double r, double dist_tl)
{
    double dl = dist_tl - r;

    return -GM_TIERRA / (r * r) + GM_LUNA / (dl * dl);
}

/* Punto donde las atracciones de Tierra y Luna se igualan */
double radio_equilibrio(double dist_tl)
{
    return dist_tl / (1.0 + sqrt(MASA_LUNA / MASA_TIERRA));
}

/* Velocidad minima para llegar al equilibrio: 1/2 v^2 = U(r_eq) - U(r1) */
double velocidad_minima_tli(const Mision *m)
{
    double d = m->dist_tierra_luna;
    double w = potencial_especifico(radio_equilibrio(d), d)
             - potencial_especifico(radio_orbital(m), d);

    return sqrt(2.0 * w);
}

/* SIMULACION  */

EventoSim avanzar_turno(const Mision *m, Punto *p, double duracion, double *r_max)
{
    double d = m->dist_tierra_luna;
    double r_eq = radio_equilibrio(d);
    double restante = duracion;
    double h, a0, a1;

    while (restante > 0.0) {
        h = (restante < PASO) ? restante : PASO;
        a0 = aceleracion_radial(p->r, d);
        p->r += p->v * h + 0.5 * a0 * h * h;
        a1 = aceleracion_radial(p->r, d);
        p->v += 0.5 * (a0 + a1) * h;
        p->t += h;
        restante -= h;

        if (p->r > *r_max) {
            *r_max = p->r;
        }
        if (p->r >= r_eq) {
            return SIM_LLEGO_EQUILIBRIO;
        }
        if (p->v <= 0.0) {
            return SIM_APOGEO;
        }
    }
    return SIM_CONTINUA;
}

static double energia_mecanica_esp(const Mision *m, const Punto *p)
{
    return 0.5 * p->v * p->v + potencial_especifico(p->r, m->dist_tierra_luna);
}

static void registrar(Reporte *rep, const Punto *p)
{
    if (rep->cantidad < MAX_TURNOS + 1) {
        rep->historial[rep->cantidad] = *p;
        rep->cantidad++;
    }
}

void ejecutar_simulacion(const Mision *m, Reporte *rep)
{
    Punto p;
    EventoSim ev;
    int horas;

    p.t = 0.0;
    p.r = radio_orbital(m);
    p.v = m->v_tli;

    rep->cantidad = 0;
    rep->resultado = MISION_EN_CURSO;
    rep->r_max = p.r;
    rep->em_inicial = energia_mecanica_esp(m, &p);
    registrar(rep, &p);

    printf("\n");
    mostrar_linea('=', 64);
    printf("  SIMULACION DE LA TRAYECTORIA TRANSLUNAR (MOTORES APAGADOS)\n");
    mostrar_linea('=', 64);
    mostrar_mision(m);
    printf("  Punto de equilibrio Tierra-Luna: %.1f km\n",
           radio_equilibrio(m->dist_tierra_luna) / 1000.0);
    printf("  Objetivo: llegar al punto de equilibrio solo por inercia.\n");
    printf("  En cada turno usted elige cuantas horas avanza la simulacion.\n");

    while (rep->resultado == MISION_EN_CURSO) {
        if (rep->cantidad >= MAX_TURNOS + 1) {
            rep->resultado = MISION_TIEMPO_AGOTADO;
            break;
        }
        mostrar_telemetria(m, &p);
        if (leer_entero("\nHoras a simular en este turno (1-48, 0 = abortar): ",
                        0, 48, &horas) != ENTRADA_OK || horas == 0) {
            rep->resultado = MISION_ABORTADA;    /* 0 o fin de entrada */
            break;
        }

        ev = avanzar_turno(m, &p, horas * SEG_POR_HORA, &rep->r_max);
        registrar(rep, &p);

        if (ev == SIM_LLEGO_EQUILIBRIO) {
            rep->resultado = MISION_EXITO;
        } else if (ev == SIM_APOGEO) {
            rep->resultado = MISION_NO_LLEGA;
        }
    }

    rep->em_final = energia_mecanica_esp(m, &p);
    mostrar_telemetria(m, &p);
    mostrar_reporte(m, rep);
}

/*  PRESENTACION  */

void mostrar_logo(void)
{
    static const char *arte[5] = {
        "      _    ____ _____ _____ __  __ ___ ____",
        "     / \\  |  _ \\_   _| ____|  \\/  |_ _/ ___|",
        "    / _ \\ | |_) || | |  _| | |\\/| || |\\___ \\",
        "   / ___ \\|  _ < | | | |___| |  | || | ___) |",
        "  /_/   \\_\\_| \\_\\|_| |_____|_|  |_|___|____/"
    };
    static const char *insignia[5] = {
        ".-----------------.",
        "|   K E R N E L   |",
        "|   P A N I C !   |",
        "|       :(        |",
        "'-----------------'"
    };
    int i;

    printf("\n");
    mostrar_linea('=', 72);
    for (i = 0; i < 5; i++) {
        printf("%-50s %s\n", arte[i], insignia[i]);
    }
    printf("\n");
    printf("        SIMULADOR DE INYECCION TRANSLUNAR (TLI)\n");
    printf("      Orion en trayectoria libre | by KERNEL PANIC\n");
    mostrar_linea('=', 72);
}

void mostrar_historia(void)
{
    printf("\n  --- LA MISION ---\n");
    printf("  Orion (26.000 kg) esta en orbita terrestre baja. La etapa ICPS\n");
    printf("  ejecuta la Inyeccion Translunar (TLI) y se desacopla: desde ese\n");
    printf("  instante los motores estan apagados y la nave viaja por inercia\n");
    printf("  (1.a Ley de Newton), frenada solo por la gravedad terrestre.\n\n");
    printf("  Si la energia alcanza, Orion llega al punto de equilibrio\n");
    printf("  gravitatorio Tierra-Luna. Si no, llega a un apogeo y vuelve.\n");
}

void mostrar_reglas(void)
{
    printf("\n  --- REGLAS DEL JUEGO ---\n");
    printf("  1. Configure la mision (o use los valores del enunciado).\n");
    printf("  2. Inicie la simulacion. Se juega por turnos: en cada uno elige\n");
    printf("     cuantas horas avanza la nave (1 a 48) o aborta (0).\n");
    printf("  3. Gana si la nave llega al punto de equilibrio Tierra-Luna.\n");
    printf("  4. Al terminar se muestra un reporte de desempeno.\n");
}

void mostrar_creditos(void)
{
    printf("\n  --- CREDITOS ---\n");
    printf("  Algoritmos y Estructuras de Datos - UTN FRRe\n");
    printf("  Ingenieria en Sistemas de Informacion\n");
    printf("  Equipo: KERNEL PANIC\n");
    printf("  Integrantes: [Gonzalez Lionel]\n");
    printf("             : [Vallejos Priscila]\n");
    printf("             : [Agostina Medina]\n");
    printf("             : [Hanabata Erika]\n");
    printf("             : [Fretes Lara]\n");
    printf("  Comision: [D]\n");
}

void mostrar_mision(const Mision *m)
{
    printf("\n  Parametros de la mision:\n");
    printf("    Masa de Orion .............. %.1f kg\n", m->masa);
    printf("    Velocidad de inyeccion ..... %.1f m/s\n", m->v_tli);
    printf("    Altura de la orbita LEO .... %.1f km\n", m->altura_leo / 1000.0);
    printf("    Distancia Tierra-Luna ...... %.1f km\n",
           m->dist_tierra_luna / 1000.0);
}

void mostrar_telemetria(const Mision *m, const Punto *p)
{
    double d = m->dist_tierra_luna;

    printf("\n");
    mostrar_linea('-', 64);
    printf("  TELEMETRIA  T+ %.2f h (%.2f dias)\n", p->t / SEG_POR_HORA,
           p->t / (24.0 * SEG_POR_HORA));
    mostrar_linea('-', 64);
    printf("  Distancia al centro de la Tierra : %.1f km\n", p->r / 1000.0);
    printf("  Distancia a la Luna ............. %.1f km\n", (d - p->r) / 1000.0);
    printf("  Velocidad ....................... %.2f m/s\n", p->v);
    printf("  Aceleracion neta (gravedad) ..... %.5f m/s^2\n",
           aceleracion_radial(p->r, d));
    printf("  Energia cinetica ................ %.4e J\n",
           energia_cinetica(m->masa, p->v));
    printf("  Energia mecanica especifica ..... %.4e J/kg\n",
           energia_mecanica_esp(m, p));
}

void mostrar_reporte(const Mision *m, const Reporte *rep)
{
    const Punto *p = rep->historial;
    double r1 = radio_orbital(m);
    double r_eq = radio_equilibrio(m->dist_tierra_luna);
    double progreso = (rep->r_max - r1) / (r_eq - r1) * 100.0;
    double v_min = velocidad_minima_tli(m);
    double deriva = fabs(rep->em_final - rep->em_inicial) / fabs(rep->em_inicial);
    int i;

    if (progreso > 100.0) {
        progreso = 100.0;
    }

    printf("\n");
    mostrar_linea('=', 64);
    printf("  REPORTE FINAL DE DESEMPENO\n");
    mostrar_linea('=', 64);
    printf("  Resultado: ");
    switch (rep->resultado) {
    case MISION_EXITO:
        printf("MISION CUMPLIDA - Orion alcanza el punto de equilibrio.\n");
        break;
    case MISION_NO_LLEGA:
        printf("INSUFICIENTE - Orion alcanza y regresa a la Tierra.\n");
        break;
    case MISION_ABORTADA:
        printf("MISION ABORTADA por el operador.\n");
        break;
    case MISION_TIEMPO_AGOTADO:
        printf("TIEMPO AGOTADO (maximo de turnos).\n", MAX_TURNOS);
        break;
    default:
        printf("EN CURSO\n");
        break;
    }

    printf("\n  Turno |  Tiempo (h) |   Distancia (km) | Velocidad (m/s)\n");
    mostrar_linea('-', 64);
    for (i = 0; i < rep->cantidad; i++) {
        printf("  %5d | %11.2f | %16.1f | %14.2f\n",
               i, p[i].t / SEG_POR_HORA, p[i].r / 1000.0, p[i].v);
    }
    mostrar_linea('-', 64);

    printf("  Maxima distancia alcanzada ..... %.1f km\n", rep->r_max / 1000.0);
    printf("  Progreso hacia el equilibrio ... %.1f %%\n", progreso);
    printf("  Velocidad de TLI usada ......... %.2f m/s\n", m->v_tli);
    printf("  Velocidad de TLI minima ........ %.2f m/s\n", v_min);
    if (m->v_tli < v_min) {
        printf("  Delta-v faltante ............... %.2f m/s\n", v_min - m->v_tli);
    }
    printf("  Verificacion: la energia mecanica se conservo (deriva %.1e).\n", deriva);
}
