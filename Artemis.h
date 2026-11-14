#ifndef Artemis.h
#define Artemis.h

// Constantes físicas

#define G_CONST  6.674e-11
#define MASA_TIERRA  5.972e24
#define MASA_LUNA   7.342e22
#define RADIO_TIERRA  6.371e6
#define GM_TIERRA  (G_CONST * MASA_TIERRA)
#define GM_LUNA  (G_CONST * MASA_LUNA)

// Valores dados por el enunciado

#define DEF_MASA       26000.0
#define DEF_V_TLI      10900.0
#define DEF_ALTURA     192000.0
#define DEF_DIST_TL    384000000.0

//Límites de validación
#define MIN_MASA       1000.0
#define MAX_MASA       1000000.0
#define MIN_V_TLI      7000.0
#define MAX_V_TLI      15000.0
#define MIN_ALTURA     160000.0
#define MAX_ALTURA     2000000.0
#define MIN_DIST_TL    356000000.0
#define MAX_DIST_TL    407000000.0

//Parametros
#define PASO           1.0
#define MAX_TURNOS     200
#define SEG_POR_HORA   3600.0

// Estructuras
typedef struct {
    double masa;            
    double v_tli;           
    double altura_leo;       
    double dist_tierra_luna; 
} Mision;

typedef struct {
    double t;
    double r;
    double v;
} Punto;

typedef enum {
    MISION_EN_CURSO,
    MISION_EXITO,
    MISION_NO_LLEGA,
    MISION_ABORTADA,
    MISION_TIEMPO_AGOTADO
} Resultado;
typedef enum {
    SIM_CONTINUA,
    SIM_LLEGO_EQUILIBRIO,
    SIM_APOGEO
} EventoSim;
typedef struct {
    Punto    historial[MAX_TURNOS + 1]
    int      cantidad;
    Resultado resultado;
    double    r_max;
    double    em_inicial;
    double    em_final;
} Reporte;

// Fisica
void   mision_por_defecto(Mision *m);
double radio_orbital(const Mision *m);
double energia_cinetica(double masa, double v);
double potencial_especifico(double r, double dist_tl);
double aceleracion_radial(double r, double dist_tl);
double radio_equilibrio(double dist_tl);
double velocidad_minima_tli(const Mision *m);

//Simulacion
EventoSim avanzar_turno(const Mision *m, Punto *p, double duracion, double *r_max);
void ejecutar_simulacion(const Mision *m, Reporte *rep);

//Presentacion
void mostrar_logo(void);
void mostrar_historia(void);
void mostrar_reglas(void);
void mostrar_creditos(void);
void mostrar_mision(const Mision *m);
void mostrar_telemetria(const Mision *m, const Punto *p);
void mostrar_reporte(const Mision *m, const Reporte *rep);

#endif
