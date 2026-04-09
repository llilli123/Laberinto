#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>

char **crear_mapa(int filas, int columnas) {
    char **mapa = (char **)malloc(filas * sizeof(char *));
    if (mapa == NULL) return NULL;

    for (int i = 0; i < filas; i++) {
        mapa[i] = (char *)malloc(columnas * sizeof(char));
        if (mapa[i] == NULL) {
            liberar_mapa(mapa, i);
            return NULL;
        }
    }
    return mapa;
}

void ensamblar_mapa_desde_grid(Pieza grid[GRID_FILAS][GRID_COLS],
                               char mapa[][100],
                               int filas_mapa,
                               int cols_mapa) {
    int fila_grid, col_grid, i, j;

    for (int f = 0; f < filas_mapa; f++) {
        for (int c = 0; c < cols_mapa; c++) {
            mapa[f][c] = '#';
        }
    }

    for (fila_grid = 0; fila_grid < GRID_FILAS; fila_grid++) {
        for (col_grid = 0; col_grid < GRID_COLS; col_grid++) {
            for (i = 0; i < ALTO; i++) {
                for (j = 0; j < ANCHO; j++) {
                    int fila_mapa = fila_grid * ALTO + i;
                    int col_mapa = col_grid * ANCHO + j;
                    mapa[fila_mapa][col_mapa] = grid[fila_grid][col_grid].forma[i][j];
                }
            }
        }
    }
}

void colocar_inicio(char **mapa, Posicion inicio) {
    mapa[inicio.fila][inicio.col] = 'E';
}

void colocar_salida(char **mapa, Posicion salida) {
    mapa[salida.fila][salida.col] = 'S';
}

void liberar_mapa(char **mapa, int filas) {
    if (mapa == NULL) return;
    for (int i = 0; i < filas; i++) {
        free(mapa[i]);
    }
    free(mapa);
}