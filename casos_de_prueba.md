# Casos de prueba – Simulador Artemis (Problema 3: TLI)

Completar la columna **Resultado obtenido** al ejecutar cada caso y marcar OK / FALLA.
Ejecutable: `./artemis_tli`. Los valores esperados corresponden al modelo con la Luna fija a distancia D.

## 1. Cálculos con los valores del enunciado

Datos: m = 26.000 kg · v_TLI = 10.900 m/s · h = 192.000 m · D = 384.000 km.

| N.º | Qué se prueba | Resultado esperado | Resultado obtenido | OK |
|---|---|---|---|---|
| 1.1 | Energía cinética inicial (inciso b) | K_i ≈ 1,5445 × 10¹² J (1,545 TJ); K_i/m ≈ 5,9405 × 10⁷ J/kg | | |
| 1.2 | Radio orbital LEO | r₁ = 6.563,0 km | | |
| 1.3 | Punto de equilibrio Tierra-Luna | r_eq ≈ 345.672,4 km | | |
| 1.4 | W_ext/m, solo Tierra (inciso c) | ≈ 5,9577 × 10⁷ J/kg | | |
| 1.5 | W_ext/m, Tierra + Luna (inciso c) | ≈ 5,9462 × 10⁷ J/kg | | |
| 1.6 | Trabajo adicional por unidad de masa | ≈ 5,7148 × 10⁴ J/kg | | |
| 1.7 | Velocidad mínima de inyección | ≈ 10.905,24 m/s | | |
| 1.8 | Velocidad de escape terrestre en LEO (inciso d) | ≈ 11.020,9 m/s | | |
| 1.9 | Aceleración a 6.563 km (inciso a) | ≈ −9,25 m/s² (frena la nave) | | |

## 2. Simulación por turnos

| N.º | Entrada | Resultado esperado | Resultado obtenido | OK |
|---|---|---|---|---|
| 2.1 | v = 10.900 m/s, turnos de 48 h hasta el final | "INSUFICIENTE": apogeo ≈ 314.418 km, progreso ≈ 90,8 %, Δv faltante ≈ 5,24 m/s | | |
| 2.2 | v = 10.950 m/s, turnos de 24 h | "MISION CUMPLIDA" (llega a ≈ 345.700 km, progreso 100 %) | | |
| 2.3 | Ingresar 0 horas en el primer turno | "MISION ABORTADA" y reporte con un solo punto | | |
| 2.4 | Ver reporte sin haber simulado | Mensaje de error, no se rompe | | |
| 2.5 | Ver el reporte después de una simulación | Se muestra el mismo reporte que al terminar | | |
| 2.6 | Cualquier simulación terminada | Deriva relativa de energía mecánica del orden de 10⁻⁵ | | |

## 3. Validaciones de entrada

Probar en el menú principal, en la configuración de la misión y en las horas por turno.

| N.º | Entrada | Resultado esperado | Resultado obtenido | OK |
|---|---|---|---|---|
| 3.1 | Letras (`abc`) | Mensaje de error y se vuelve a pedir | | |
| 3.2 | Línea vacía (solo Enter) | "No ingresó ningún valor" y se vuelve a pedir | | |
| 3.3 | Opción fuera de rango (`9`, `-1`) | Mensaje con el rango permitido | | |
| 3.4 | Decimal donde se pide un entero (`1.5`) | Mensaje de error | | |
| 3.5 | Símbolos mezclados (`1;DROP`) | Mensaje de error | | |
| 3.6 | `nan`, `inf` en un dato real | Rechazado | | |
| 3.7 | `1e99` en un dato real | "Valor fuera de rango" | | |
| 3.8 | Masa = 99999999 | "Valor fuera de rango", muestra 1000 – 1000000 | | |
| 3.9 | Coma decimal (`10900,5`) | Se acepta | | |
| 3.10 | Dos separadores decimales (`10.9.5`) | Mensaje de error | | |
| 3.11 | Línea muy larga (más de 128 caracteres) | "Demasiado larga", sin romper la lectura siguiente | | |
| 3.12 | Fin de entrada (Ctrl+D en Linux, Ctrl+Z + Enter en Windows) | Cierre ordenado, sin bucle infinito | | |
| 3.13 | Valores límite en la configuración (mínimos y máximos exactos) | Se aceptan | | |
| 3.14 | Un valor justo fuera del límite (por ejemplo v = 15000,1) | Se rechaza | | |

## 4. Compilación

| N.º | Qué se prueba | Resultado esperado | Resultado obtenido | OK |
|---|---|---|---|---|
| 4.1 | `make` desde cero | Compila sin warnings con `-Wall -Wextra -pedantic` | | |
| 4.2 | `make clean` y volver a `make` | Funciona | | |
| 4.3 | Compilación sin `make` (comando `gcc` del README) | Funciona | | |
| 4.4 | Probar en Windows y en Linux | Mismo comportamiento | | |
