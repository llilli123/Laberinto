#include "generador.h"
#include <string.h>

/* =========================================================
   FUNCIONES INTERNAS PRIVADAS DEL MÓDULO
   ========================================================= */

/*
 * Crea una pieza vacía para inicializar el grid.
 * Esta función es interna al módulo.
 */
static Pieza crear_pieza_vacia(void) {
    Pieza p;
    int i, j;

    strcpy(p.nombre, "VACIA");

    for (i = 0; i < ALTO; i++) {
        for (j = 0; j < ANCHO; j++) {
            p.forma[i][j] = '#';
        }
        p.forma[i][ANCHO] = '\0';
    }

    p.arriba = 0;
    p.abajo = 0;
    p.izquierda = 0;
    p.derecha = 0;

    return p;
}

/*
 * Mezcla aleatoriamente un arreglo de índices para probar piezas
 * en orden aleatorio y evitar siempre el mismo patrón.
 */
static void mezclar_indices(int indices[], int n) {
    int i;

    for (i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }
}

/*
 * Llena una matriz auxiliar con ceros.
 */
static void limpiar_matriz_ruta(int matriz[GRID_FILAS][GRID_COLS]) {
    int i, j;

    for (i = 0; i < GRID_FILAS; i++) {
        for (j = 0; j < GRID_COLS; j++) {
            matriz[i][j] = 0;
        }
    }
}

/* =========================================================
   FUNCIONES DE INICIALIZACIÓN
   ========================================================= */

void generador_inicializar_random(void) {
    srand((unsigned int)time(NULL));
}

/* =========================================================
   FUNCIONES DE APOYO PARA EL GRID
   ========================================================= */

void limpiar_grid(Pieza grid[GRID_FILAS][GRID_COLS]) {
    int i, j;
    Pieza vacia = crear_pieza_vacia();

    for (i = 0; i < GRID_FILAS; i++) {
        for (j = 0; j < GRID_COLS; j++) {
            grid[i][j] = vacia;
        }
    }
}

int posicion_grid_valida(int fila, int col) {
    return (fila >= 0 && fila < GRID_FILAS && col >= 0 && col < GRID_COLS);
}

int celda_esta_en_ruta(const RutaPrincipal *ruta, int fila, int col) {
    int i;

    if (ruta == NULL) {
        return 0;
    }

    for (i = 0; i < ruta->longitud; i++) {
        if (ruta->celdas[i].fila == fila && ruta->celdas[i].col == col) {
            return 1;
        }
    }

    return 0;
}

int agregar_celda_a_ruta(RutaPrincipal *ruta, int fila, int col) {
    if (ruta == NULL) {
        return 0;
    }

    if (!posicion_grid_valida(fila, col)) {
        return 0;
    }

    if (ruta->longitud >= MAX_RUTA_PRINCIPAL) {
        return 0;
    }

    if (celda_esta_en_ruta(ruta, fila, col)) {
        return 0;
    }

    ruta->celdas[ruta->longitud].fila = fila;
    ruta->celdas[ruta->longitud].col = col;
    ruta->longitud++;

    return 1;
}

/* =========================================================
   COMPATIBILIDAD Y VALIDACIÓN DE PIEZAS
   ========================================================= */

int es_compatible_izquierda(const Pieza *pieza_izquierda, const Pieza *pieza_candidata) {
    if (pieza_izquierda == NULL || pieza_candidata == NULL) {
        return 0;
    }

    return (pieza_izquierda->derecha == pieza_candidata->izquierda);
}

int es_compatible_arriba(const Pieza *pieza_superior, const Pieza *pieza_candidata) {
    if (pieza_superior == NULL || pieza_candidata == NULL) {
        return 0;
    }

    return (pieza_superior->abajo == pieza_candidata->arriba);
}

int pieza_es_valida_en_posicion(
    Pieza grid[GRID_FILAS][GRID_COLS],
    int fila,
    int col,
    const Pieza *candidata
) {
    if (!posicion_grid_valida(fila, col) || candidata == NULL) {
        return 0;
    }

    /* Validar contra vecino izquierdo si existe */
    if (col > 0) {
        if (!es_compatible_izquierda(&grid[fila][col - 1], candidata)) {
            return 0;
        }
    }

    /* Validar contra vecino superior si existe */
    if (fila > 0) {
        if (!es_compatible_arriba(&grid[fila - 1][col], candidata)) {
            return 0;
        }
    }

    return 1;
}

/* =========================================================
   SELECCIÓN Y COLOCACIÓN DE PIEZAS
   ========================================================= */

int seleccionar_pieza_compatible(
    Pieza grid[GRID_FILAS][GRID_COLS],
    int fila,
    int col,
    const Pieza catalogo[],
    int total_catalogo,
    Pieza *pieza_resultado
) {
    int i;
    int indices[MAX_PIEZAS];

    if (catalogo == NULL || pieza_resultado == NULL || total_catalogo <= 0) {
        return 0;
    }

    if (total_catalogo > MAX_PIEZAS) {
        return 0;
    }

    for (i = 0; i < total_catalogo; i++) {
        indices[i] = i;
    }

    mezclar_indices(indices, total_catalogo);

    for (i = 0; i < total_catalogo; i++) {
        Pieza candidata = catalogo[indices[i]];

        if (pieza_es_valida_en_posicion(grid, fila, col, &candidata)) {
            *pieza_resultado = candidata;
            return 1;
        }
    }

    return 0;
}

int colocar_pieza_en_grid(
    Pieza grid[GRID_FILAS][GRID_COLS],
    int fila,
    int col,
    const Pieza *pieza
) {
    if (!posicion_grid_valida(fila, col) || pieza == NULL) {
        return 0;
    }

    grid[fila][col] = *pieza;
    return 1;
}

/* =========================================================
   GENERACIÓN DE RUTA PRINCIPAL
   ========================================================= */

void inicializar_ruta_principal(RutaPrincipal *ruta) {
    if (ruta == NULL) {
        return;
    }

    ruta->longitud = 0;
}

int generar_ruta_principal(
    RutaPrincipal *ruta,
    int fila_inicio,
    int col_inicio,
    int fila_fin,
    int col_fin
) {
    int fila_actual, col_actual;
    int seguridad = 0;

    if (ruta == NULL) {
        return 0;
    }

    if (!posicion_grid_valida(fila_inicio, col_inicio) ||
        !posicion_grid_valida(fila_fin, col_fin)) {
        return 0;
    }

    inicializar_ruta_principal(ruta);

    fila_actual = fila_inicio;
    col_actual = col_inicio;

    if (!agregar_celda_a_ruta(ruta, fila_actual, col_actual)) {
        return 0;
    }

    /*
     * Estrategia simple:
     * avanzar aleatoriamente hacia abajo o derecha hasta llegar al destino.
     * Esta versión asume un destino "abajo-derecha" respecto al inicio,
     * por ejemplo (0,0) -> (GRID_FILAS-1, GRID_COLS-1).
     */
    while ((fila_actual != fila_fin || col_actual != col_fin) && seguridad < 1000) {
        int puede_bajar = (fila_actual < fila_fin);
        int puede_derecha = (col_actual < col_fin);

        seguridad++;

        if (puede_bajar && puede_derecha) {
            if (rand() % 2 == 0) {
                fila_actual++;
            } else {
                col_actual++;
            }
        } else if (puede_bajar) {
            fila_actual++;
        } else if (puede_derecha) {
            col_actual++;
        } else {
            break;
        }

        if (!agregar_celda_a_ruta(ruta, fila_actual, col_actual)) {
            return 0;
        }
    }

    return (fila_actual == fila_fin && col_actual == col_fin);
}

void marcar_ruta_en_matriz(
    const RutaPrincipal *ruta,
    int matriz_ruta[GRID_FILAS][GRID_COLS]
) {
    int i;

    if (ruta == NULL) {
        return;
    }

    limpiar_matriz_ruta(matriz_ruta);

    for (i = 0; i < ruta->longitud; i++) {
        int f = ruta->celdas[i].fila;
        int c = ruta->celdas[i].col;

        if (posicion_grid_valida(f, c)) {
            matriz_ruta[f][c] = 1;
        }
    }
}

/* =========================================================
   GENERACIÓN COMPLETA DEL LABERINTO
   ========================================================= */

int generar_grid(
    Pieza grid[GRID_FILAS][GRID_COLS],
    const Pieza catalogo[],
    int total_catalogo
) {
    int i, j;

    if (catalogo == NULL || total_catalogo <= 0) {
        return 0;
    }

    limpiar_grid(grid);

    for (i = 0; i < GRID_FILAS; i++) {
        for (j = 0; j < GRID_COLS; j++) {
            Pieza seleccionada;
            int exito = seleccionar_pieza_compatible(
                grid,
                i,
                j,
                catalogo,
                total_catalogo,
                &seleccionada
            );

            if (!exito) {
                return 0;
            }

            if (!colocar_pieza_en_grid(grid, i, j, &seleccionada)) {
                return 0;
            }
        }
    }

    return 1;
}

int generar_laberinto(
    Pieza grid[GRID_FILAS][GRID_COLS],
    const Pieza catalogo[],
    int total_catalogo
) {
    RutaPrincipal ruta;
    int matriz_ruta[GRID_FILAS][GRID_COLS];

    /*
     * Esta versión base:
     * 1. genera una ruta principal lógica
     * 2. la marca en una matriz auxiliar
     * 3. genera el grid completo de piezas compatibles
     *
     * En una versión más avanzada, la ruta servirá para forzar piezas
     * concretas según dirección de entrada/salida.
     */

    if (!generar_ruta_principal(&ruta, 0, 0, GRID_FILAS - 1, GRID_COLS - 1)) {
        return 0;
    }

    marcar_ruta_en_matriz(&ruta, matriz_ruta);

    /*
     * Actualmente la matriz_ruta queda lista para futuras mejoras.
     * Por ejemplo:
     * - forzar pasillos en la ruta
     * - evitar demasiados callejones
     * - colocar inicio y salida en celdas concretas
     */

    return generar_grid(grid, catalogo, total_catalogo);
}

int generar_laberinto_con_reintentos(
    Pieza grid[GRID_FILAS][GRID_COLS],
    const Pieza catalogo[],
    int total_catalogo,
    int max_intentos
) {
    int intento;

    if (max_intentos <= 0) {
        return 0;
    }

    for (intento = 0; intento < max_intentos; intento++) {
        if (generar_laberinto(grid, catalogo, total_catalogo)) {
            return 1;
        }
    }

    return 0;
}

/* =========================================================
   DEPURACIÓN / VISUALIZACIÓN
   ========================================================= */

void imprimir_grid_nombres(Pieza grid[GRID_FILAS][GRID_COLS]) {
    int i, j;

    printf("=== GRID DE PIEZAS ===\n");
    for (i = 0; i < GRID_FILAS; i++) {
        for (j = 0; j < GRID_COLS; j++) {
            printf("[%s]", grid[i][j].nombre);
        }
        printf("\n");
    }
}

void imprimir_ruta_principal(const RutaPrincipal *ruta) {
    int i;

    if (ruta == NULL) {
        printf("Ruta principal: NULL\n");
        return;
    }

    printf("=== RUTA PRINCIPAL ===\n");
    printf("Longitud: %d\n", ruta->longitud);

    for (i = 0; i < ruta->longitud; i++) {
        printf("Paso %d -> (%d, %d)\n",
               i,
               ruta->celdas[i].fila,
               ruta->celdas[i].col);
    }
}