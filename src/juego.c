#include <stdio.h>
#include <string.h>

#include "juego.h"
#include "pieza.h"
#include "catalogo_piezas.h"
#include "generador.h"
#include "input.h"
#include "render.h"
#include "jugador.h"
#include "lista.h"
#include "validador.h"
#include "ranking.h"

#define MAPA_MAX 100
#define OBJETOS_INICIALES 3

typedef struct {
    Pieza catalogo[MAX_PIEZAS];
    int total_catalogo;

    Pieza grid[GRID_FILAS][GRID_COLS];

    char mapa_base[MAPA_MAX][MAPA_MAX];
    char mapa_vista[MAPA_MAX][MAPA_MAX];

    int filas_mapa;
    int cols_mapa;

    Posicion inicio;
    Posicion salida;
    Posicion jugador;

    Nodo *inventario;

    int puntaje;
    int vidas;
    int terminado;
    int victoria;
} EstadoJuego;

static EstadoJuego juego;

/* =========================================================
   FUNCIONES PRIVADAS
   ========================================================= */

static void limpiar_mapa_base(void) {
    int i, j;

    for (i = 0; i < MAPA_MAX; i++) {
        for (j = 0; j < MAPA_MAX; j++) {
            juego.mapa_base[i][j] = '#';
        }
    }
}

static void copiar_grid_a_mapa_base(void) {
    int fila_grid, col_grid, i, j;

    limpiar_mapa_base();

    juego.filas_mapa = GRID_FILAS * ALTO;
    juego.cols_mapa = GRID_COLS * ANCHO;

    for (fila_grid = 0; fila_grid < GRID_FILAS; fila_grid++) {
        for (col_grid = 0; col_grid < GRID_COLS; col_grid++) {
            Pieza *pieza_actual = &juego.grid[fila_grid][col_grid];

            for (i = 0; i < ALTO; i++) {
                for (j = 0; j < ANCHO; j++) {
                    int fila_mapa = fila_grid * ALTO + i;
                    int col_mapa = col_grid * ANCHO + j;
                    juego.mapa_base[fila_mapa][col_mapa] = pieza_actual->forma[i][j];
                }
            }
        }
    }
}

static int buscar_simbolo_en_mapa(char simbolo, Posicion *pos) {
    int i, j;

    if (pos == NULL) {
        return 0;
    }

    for (i = 0; i < juego.filas_mapa; i++) {
        for (j = 0; j < juego.cols_mapa; j++) {
            if (juego.mapa_base[i][j] == simbolo) {
                pos->fila = i;
                pos->col = j;
                return 1;
            }
        }
    }

    return 0;
}

static int buscar_primera_celda_libre(Posicion *pos) {
    int i, j;

    if (pos == NULL) {
        return 0;
    }

    for (i = 0; i < juego.filas_mapa; i++) {
        for (j = 0; j < juego.cols_mapa; j++) {
            if (juego.mapa_base[i][j] == ' ') {
                pos->fila = i;
                pos->col = j;
                return 1;
            }
        }
    }

    return 0;
}

static int buscar_ultima_celda_libre(Posicion *pos) {
    int i, j;

    if (pos == NULL) {
        return 0;
    }

    for (i = juego.filas_mapa - 1; i >= 0; i--) {
        for (j = juego.cols_mapa - 1; j >= 0; j--) {
            if (juego.mapa_base[i][j] == ' ') {
                pos->fila = i;
                pos->col = j;
                return 1;
            }
        }
    }

    return 0;
}

static int buscar_celda_libre_desde_inicio(Posicion *pos) {
    for (int i = 0; i < juego.filas_mapa; i++) {
        for (int j = 0; j < juego.cols_mapa; j++) {
            if (juego.mapa_base[i][j] == ' ') {
                pos->fila = i;
                pos->col = j;
                return 1;
            }
        }
    }
    return 0;
}

static int buscar_celda_libre_desde_final(Posicion *pos) {
    for (int i = juego.filas_mapa - 1; i >= 0; i--) {
        for (int j = juego.cols_mapa - 1; j >= 0; j--) {
            if (juego.mapa_base[i][j] == ' ') {
                pos->fila = i;
                pos->col = j;
                return 1;
            }
        }
    }
    return 0;
}

static void colocar_inicio_y_salida_en_mapa(void) {
    if (buscar_celda_libre_desde_inicio(&juego.inicio)) {
        juego.mapa_base[juego.inicio.fila][juego.inicio.col] = 'E';
    }

    if (buscar_celda_libre_desde_final(&juego.salida)) {
        juego.mapa_base[juego.salida.fila][juego.salida.col] = 'S';
    }
}

static void colocar_objetos_aleatorios(int cantidad) {
    int colocados = 0;
    int intentos = 0;

    while (colocados < cantidad && intentos < 1000) {
        int f = rand() % juego.filas_mapa;
        int c = rand() % juego.cols_mapa;

        if (juego.mapa_base[f][c] == ' ') {
            juego.mapa_base[f][c] = '*';
            colocados++;
        }

        intentos++;
    }
}

static void crear_punteros_filas(char *filas_ptr[MAPA_MAX]) {
    int i;

    for (i = 0; i < juego.filas_mapa; i++) {
        filas_ptr[i] = juego.mapa_base[i];
    }
}

static int validar_mapa_generado(void) {
    char *filas_ptr[MAPA_MAX];
    crear_punteros_filas(filas_ptr);
    return bfs_hay_camino(filas_ptr, juego.filas_mapa, juego.cols_mapa);
}

static void preparar_mapa_vista(void) {
    int i, j;

    for (i = 0; i < juego.filas_mapa; i++) {
        for (j = 0; j < juego.cols_mapa; j++) {
            juego.mapa_vista[i][j] = juego.mapa_base[i][j];
        }
    }

    juego.mapa_vista[juego.jugador.fila][juego.jugador.col] = 'J';
}

static void recoger_objeto_si_existe(void) {
    if (juego.mapa_base[juego.jugador.fila][juego.jugador.col] == '*') {
        insertar_item(&juego.inventario, "Objeto", '*', 1);
        juego.mapa_base[juego.jugador.fila][juego.jugador.col] = ' ';
        juego.puntaje += 10;
    }
}

static void mostrar_inventario_en_pantalla(void) {
    printf("\n");
    mostrar_inventario(juego.inventario);
}

static int accion_a_direccion(Accion accion, char *direccion) {
    if (direccion == NULL) {
        return 0;
    }

    switch (accion) {
        case ACCION_ARRIBA:
            *direccion = 'W';
            return 1;
        case ACCION_ABAJO:
            *direccion = 'S';
            return 1;
        case ACCION_IZQUIERDA:
            *direccion = 'A';
            return 1;
        case ACCION_DERECHA:
            *direccion = 'D';
            return 1;
        default:
            return 0;
    }
}

static int construir_juego_valido(void) {
    int intento;
    char *filas_ptr[MAPA_MAX];

    for (intento = 0; intento < 50; intento++) {
        if (!generar_laberinto_con_reintentos(juego.grid, juego.catalogo, juego.total_catalogo, MAX_INTENTOS_GENERACION)) {
            continue;
        }

        copiar_grid_a_mapa_base();
        colocar_inicio_y_salida_en_mapa();


        crear_punteros_filas(filas_ptr);

        if (!validar_mapa_generado()) {
            continue;
        }

        colocar_objetos_aleatorios(OBJETOS_INICIALES);
        return 1;
    }

    return 0;
}

static int reiniciar_laberinto(void) {
    if (!construir_juego_valido()) {
        return 0;
    }

    juego.jugador = inicializar_jugador(juego.inicio.fila, juego.inicio.col);
    juego.victoria = 0;

    return 1;
}

/* =========================================================
   INTERFAZ PÚBLICA
   ========================================================= */

int juego_init(void) {
    ranking_inicializar();

    juego.total_catalogo = 0;
    juego.inventario = NULL;
    juego.puntaje = 0;
    juego.vidas = 3;
    juego.terminado = 0;
    juego.victoria = 0;

    generador_inicializar_random();
    cargar_catalogo_piezas(juego.catalogo, &juego.total_catalogo);

    if (!construir_juego_valido()) {
        return 0;
    }

    juego.jugador = inicializar_jugador(juego.inicio.fila, juego.inicio.col);

    return 1;
}

void juego_run(void) {
    while (!juego.terminado) {
        char tecla;
        Accion accion;
        char direccion;
        char *filas_ptr[MAPA_MAX];

        limpiar_pantalla();
        mostrar_menu();
        mostrar_leyenda();

        preparar_mapa_vista();
        dibujar_mapa(juego.mapa_vista, juego.filas_mapa, juego.cols_mapa);
        mostrar_estado(juego.vidas, juego.puntaje, "Explora el laberinto.");
        mostrar_inventario_en_pantalla();

        printf("\nIngresa una tecla: ");
        tecla = leer_tecla();
        accion = convertir_tecla_a_movimiento(tecla);

        if (accion == ACCION_SALIR) {
            juego.terminado = 1;
            break;
        }

        if (accion == ACCION_INVALIDA) {
            continue;
        }

        if (accion_a_direccion(accion, &direccion)) {
            crear_punteros_filas(filas_ptr);
            mover_jugador(&juego.jugador, direccion, filas_ptr, juego.filas_mapa, juego.cols_mapa);
            recoger_objeto_si_existe();

            if (llego_a_salida(juego.jugador, juego.salida)) {
                juego.victoria = 1;
                juego.puntaje += 100;

                limpiar_pantalla();
                mostrar_victoria();
                printf("\nHas completado el laberinto. Se generara uno nuevo...\n");
                printf("Presiona una tecla para continuar...");
                leer_tecla();

                if (!reiniciar_laberinto()) {
                    printf("\nError: no se pudo generar un nuevo laberinto.\n");
                    juego.terminado = 1;
                }

                continue;
            }
        }
    }

    limpiar_pantalla();
    mostrar_mensaje("Has salido del juego.");
    ranking_agregar("Jugador", juego.puntaje);
    ranking_mostrar();
}

void juego_cleanup(void) {
    liberar_lista(&juego.inventario);
}