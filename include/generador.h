//
// Created by jorge on 4/8/2026.
//

#ifndef LABERINTO_GENERADOR_H
#define LABERINTO_GENERADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pieza.h"

/* =========================================================
   CONFIGURACIÓN GENERAL DEL GRID
   Si ya tienes estos valores definidos en config.h
   o en otro archivo, puedes quitar estos #define
   y simplemente incluir ese header aquí.
   ========================================================= */
#ifndef GRID_FILAS
#define GRID_FILAS 3
#endif

#ifndef GRID_COLS
#define GRID_COLS 3
#endif

#ifndef MAX_INTENTOS_GENERACION
#define MAX_INTENTOS_GENERACION 100
#endif

#ifndef MAX_RUTA_PRINCIPAL
#define MAX_RUTA_PRINCIPAL (GRID_FILAS * GRID_COLS)
#endif

/* =========================================================
   ESTRUCTURAS AUXILIARES DEL GENERADOR
   ========================================================= */

/* Representa una celda dentro del grid lógico de piezas */
typedef struct {
    int fila;
    int col;
} CeldaGrid;

/* Guarda la ruta principal desde inicio hasta salida */
typedef struct {
    CeldaGrid celdas[MAX_RUTA_PRINCIPAL];
    int longitud;
} RutaPrincipal;

/* =========================================================
   FUNCIONES DE INICIALIZACIÓN
   ========================================================= */

/*
 * Inicializa la semilla de números aleatorios.
 * Debe llamarse una sola vez al inicio del programa.
 */
void generador_inicializar_random(void);

/* =========================================================
   FUNCIONES DE APOYO PARA EL GRID
   ========================================================= */

/*
 * Limpia el grid de piezas.
 * Deja cada posición con una pieza "vacía" o con valores por defecto.
 *
 * Parámetros:
 *  - grid: matriz de piezas del laberinto
 */
void limpiar_grid(Pieza grid[GRID_FILAS][GRID_COLS]);

/*
 * Verifica si una posición (fila, col) está dentro de los límites del grid.
 *
 * Retorna:
 *  - 1 si está dentro del grid
 *  - 0 si está fuera de rango
 */
int posicion_grid_valida(int fila, int col);

/*
 * Indica si una celda ya forma parte de una ruta principal.
 *
 * Parámetros:
 *  - ruta: estructura con la ruta principal
 *  - fila, col: posición a verificar
 *
 * Retorna:
 *  - 1 si la celda ya está en la ruta
 *  - 0 si no está
 */
int celda_esta_en_ruta(const RutaPrincipal *ruta, int fila, int col);

/*
 * Agrega una celda a la ruta principal.
 *
 * Retorna:
 *  - 1 si se agregó correctamente
 *  - 0 si no se pudo agregar (por ejemplo, ruta llena)
 */
int agregar_celda_a_ruta(RutaPrincipal *ruta, int fila, int col);

/* =========================================================
   COMPATIBILIDAD Y VALIDACIÓN DE PIEZAS
   ========================================================= */

/*
 * Verifica si la pieza candidata es compatible con la pieza vecina de la izquierda.
 *
 * Regla:
 *  - La derecha de la pieza izquierda debe coincidir con la izquierda de la candidata.
 *
 * Retorna:
 *  - 1 si son compatibles
 *  - 0 si no lo son
 */
int es_compatible_izquierda(const Pieza *pieza_izquierda, const Pieza *pieza_candidata);

/*
 * Verifica si la pieza candidata es compatible con la pieza vecina superior.
 *
 * Regla:
 *  - El abajo de la pieza superior debe coincidir con el arriba de la candidata.
 *
 * Retorna:
 *  - 1 si son compatibles
 *  - 0 si no lo son
 */
int es_compatible_arriba(const Pieza *pieza_superior, const Pieza *pieza_candidata);

/*
 * Verifica si una pieza candidata puede colocarse en una posición específica del grid.
 *
 * Esta función debe revisar al menos:
 *  - compatibilidad con vecino izquierdo (si existe)
 *  - compatibilidad con vecino superior (si existe)
 *
 * Parámetros:
 *  - grid: matriz actual de piezas
 *  - fila, col: posición donde se quiere colocar la pieza
 *  - candidata: pieza a evaluar
 *
 * Retorna:
 *  - 1 si la pieza puede colocarse
 *  - 0 si no puede colocarse
 */
int pieza_es_valida_en_posicion(
    Pieza grid[GRID_FILAS][GRID_COLS],
    int fila,
    int col,
    const Pieza *candidata
);

/* =========================================================
   SELECCIÓN Y COLOCACIÓN DE PIEZAS
   ========================================================= */

/*
 * Busca una pieza compatible dentro del catálogo para una posición específica.
 *
 * Parámetros:
 *  - grid: grid actual
 *  - fila, col: posición a llenar
 *  - catalogo: arreglo de piezas disponibles
 *  - total_catalogo: cantidad de piezas en el catálogo
 *  - pieza_resultado: salida, donde se guarda la pieza seleccionada
 *
 * Retorna:
 *  - 1 si encontró una pieza válida
 *  - 0 si no encontró ninguna
 */
int seleccionar_pieza_compatible(
    Pieza grid[GRID_FILAS][GRID_COLS],
    int fila,
    int col,
    const Pieza catalogo[],
    int total_catalogo,
    Pieza *pieza_resultado
);

/*
 * Coloca una pieza en una celda del grid.
 *
 * Retorna:
 *  - 1 si la posición era válida y se colocó
 *  - 0 si la posición era inválida
 */
int colocar_pieza_en_grid(
    Pieza grid[GRID_FILAS][GRID_COLS],
    int fila,
    int col,
    const Pieza *pieza
);

/* =========================================================
   GENERACIÓN DE RUTA PRINCIPAL
   ========================================================= */

/*
 * Inicializa una ruta principal vacía.
 */
void inicializar_ruta_principal(RutaPrincipal *ruta);

/*
 * Genera una ruta principal desde una celda de inicio hasta una celda final.
 *
 * Esta ruta representa el "camino base" del laberinto a nivel de piezas.
 * Luego puede usarse para obligar ciertas conexiones entre piezas.
 *
 * Parámetros:
 *  - ruta: donde se almacenará la ruta generada
 *  - fila_inicio, col_inicio: inicio de la ruta
 *  - fila_fin, col_fin: final de la ruta
 *
 * Retorna:
 *  - 1 si la ruta fue generada
 *  - 0 si falló
 */
int generar_ruta_principal(
    RutaPrincipal *ruta,
    int fila_inicio,
    int col_inicio,
    int fila_fin,
    int col_fin
);

/*
 * Marca en el grid lógico las posiciones que pertenecen a la ruta principal.
 * Esta función es opcional según el diseño final del generador.
 *
 * Parámetros:
 *  - ruta: ruta principal
 *  - matriz_ruta: matriz auxiliar de enteros donde:
 *      1 = la celda pertenece a la ruta
 *      0 = no pertenece
 */
void marcar_ruta_en_matriz(
    const RutaPrincipal *ruta,
    int matriz_ruta[GRID_FILAS][GRID_COLS]
);

/* =========================================================
   GENERACIÓN COMPLETA DEL LABERINTO
   ========================================================= */

/*
 * Rellena completamente el grid con piezas válidas usando el catálogo dado.
 *
 * Estrategia esperada:
 *  - recorrer el grid
 *  - para cada celda, elegir una pieza compatible
 *  - si no se puede, reintentar o abortar según la lógica del módulo
 *
 * Parámetros:
 *  - grid: matriz de piezas a llenar
 *  - catalogo: catálogo de piezas disponibles
 *  - total_catalogo: número total de piezas en el catálogo
 *
 * Retorna:
 *  - 1 si el grid fue generado correctamente
 *  - 0 si falló la generación
 */
int generar_grid(
    Pieza grid[GRID_FILAS][GRID_COLS],
    const Pieza catalogo[],
    int total_catalogo
);

/*
 * Genera el laberinto completo usando una ruta principal y luego rellenando
 * las demás celdas con piezas compatibles.
 *
 * Esta puede ser la función "principal" del módulo generador.
 *
 * Flujo recomendado:
 *  1. limpiar grid
 *  2. generar ruta principal
 *  3. colocar piezas base en la ruta
 *  4. rellenar espacios restantes
 *  5. devolver éxito o fallo
 *
 * Parámetros:
 *  - grid: salida, grid final de piezas
 *  - catalogo: piezas disponibles
 *  - total_catalogo: cantidad de piezas
 *
 * Retorna:
 *  - 1 si el laberinto fue generado correctamente
 *  - 0 si falló
 */
int generar_laberinto(
    Pieza grid[GRID_FILAS][GRID_COLS],
    const Pieza catalogo[],
    int total_catalogo
);

/*
 * Intenta generar el laberinto varias veces hasta lograr un resultado válido
 * o hasta agotar el número máximo de intentos.
 *
 * Parámetros:
 *  - grid: salida, grid generado
 *  - catalogo: piezas disponibles
 *  - total_catalogo: cantidad de piezas
 *  - max_intentos: número máximo de intentos permitidos
 *
 * Retorna:
 *  - 1 si se logró generar
 *  - 0 si no se logró
 */
int generar_laberinto_con_reintentos(
    Pieza grid[GRID_FILAS][GRID_COLS],
    const Pieza catalogo[],
    int total_catalogo,
    int max_intentos
);

/* =========================================================
   DEPURACIÓN / VISUALIZACIÓN
   ========================================================= */

/*
 * Imprime por consola los nombres de las piezas colocadas en el grid.
 * Útil para depuración.
 */
void imprimir_grid_nombres(Pieza grid[GRID_FILAS][GRID_COLS]);

/*
 * Imprime por consola la ruta principal generada.
 * Útil para depuración.
 */
void imprimir_ruta_principal(const RutaPrincipal *ruta);

#endif //LABERINTO_GENERADOR_H
