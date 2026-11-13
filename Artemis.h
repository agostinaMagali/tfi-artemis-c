// Constantes físicas

#define G_CONST  6.674e-11
#define MASA_TIERRA  5.972e24
#define MASA_LUNA   7.342e22
#define RADIO_TIERRA  6.371e6
#define RADIO_LUNA  1.737e6
#define GM_TIERRA  (G_CONST * MASA_TIERRA)
#define GM_LUNA  (G_CONST * MASA_LUNA)

// Valores dados por el enunciado

#define DEF_MASA       26000.0
#define DEF_V_TLI      10900.0
#define DEF_ALTURA     192000.0
#define DEF_DIST_TL    384000000.0
#define VEL_GASES      4500.0

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

// Funciones

void   mision_por_defecto(Mision *m);
double radio_orbital(const Mision *m);
double energia_cinetica(double masa, double v);
double potencial_especifico(double r, double dist_tl);
double aceleracion_radial(double r, double dist_tl);
double radio_equilibrio(double dist_tl);
double trabajo_por_masa_total(const Mision *m);
double trabajo_adicional_por_masa(const Mision *m);
double velocidad_minima_tli(const Mision *m);
double velocidad_circular(double gm, double r);
double velocidad_escape(double gm, double r);
double masa_propelente(double masa_final, double delta_v, double v_gases);

void mostrar_analisis_a(const Mision *m);
void mostrar_analisis_b(const Mision *m);
void mostrar_analisis_c(const Mision *m);
void mostrar_analisis_d(const Mision *m);
