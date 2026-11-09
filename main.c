#include <stdio.h>
#include <stdlib.h>
//el Integrante 4 declarará las estructuras y constantes.
#include "artemis.h" 
// Incluimos las validaciones del Integrante 5.
#include "validaciones.h" 

int main() {
    int opcion;
    int simulacionActiva = 1;

    // instanciar la estructura de la nave (definida en artemis.h por otro compañero)
    // struct Nave orion;
    // orion.masa = 26000.0;
    // orion.velocidad = 10900.0;
    
    printf("==================================================\n");
    printf("   SIMULADOR DE MISIONES ARTEMIS - ESCENARIO 3\n");
    printf("==================================================\n");

    while (simulacionActiva) {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Analizar Inercia y Fuerza Gravitatoria (1ra Ley de Newton)\n");
        printf("2. Calcular Energia Cinetica Inicial\n");
        printf("3. Determinar Trabajo Adicional Minimo (Wext)\n");
        printf("4. Justificar Consumo de Combustible (Ida vs Vuelta)\n");
        printf("5. Generar Reporte Final y Salir\n");
        printf("==================================================\n");
        
        // Se utiliza la función del compañero (Integrante 5) para que no se rompa si escriben letras
        opcion = validarEntradaEntera("Seleccione una opcion (1-5): ", 1, 5);

        switch (opcion) {
            case 1:
                // Llamada a la función del Integrante 2 (en simulador.c)
                // analizarInerciaOrion();
                printf("\n[Ejecutando analisis de inercia...]\n");
                break;
            case 2:
                // Llamada a la función del Integrante 2 (en simulador.c)
                // calcularEnergiaCinetica(orion);
                printf("\n[Calculando energia cinetica...]\n");
                break;
            case 3:
                // Llamada a la función del Integrante 3 (en simulador.c)
                // calcularTrabajoAdicional(orion);
                printf("\n[Calculando Trabajo Adicional Minimo...]\n");
                break;
            case 4:
                // Llamada a la función del Integrante 3 (en simulador.c)
                // justificarCombustible();
                printf("\n[Generando justificacion energetica...]\n");
                break;
            case 5:
                printf("\nGenerando reporte final de la simulacion...\n");
                printf("Cerrando los sistemas de la nave Orion. Buen viaje.\n");
                simulacionActiva = 0;
                break;
            default:
                printf("\nError: Opcion no valida.\n");
                break;
        }
    }

    return 0;
}
