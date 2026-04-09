#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>

char **crear_mapa(int filas, int columnas) {
    // Reservar memoria para el arreglo de punteros a filas
    char **mapa = (char **)malloc(filas * sizeof(char *));
    if (mapa == NULL) return NULL;

    // Reservar memoria para cada columna dentro de la fila
    for (int i = 0; i < filas; i++) {
        mapa[i] = (char *)malloc(columnas * sizeof(char));
        if (mapa[i] == NULL) {
            // Manejo de error: liberar lo reservado si falla a la mitad
            liberar_mapa(mapa, i);
            return NULL;
        }
    }
    return mapa;
}

void ensamblar_mapa(char **mapa_final, char ***piezas_grid, int filas_grid, int col_grid, int alto_pieza, int ancho_pieza) {
    // Riesgo mitigado: Copiar manteniendo dimensiones correctas
    for (int fila_g = 0; fila_g < filas_grid; fila_g++) {
        for (int col_g = 0; col_g < col_grid; col_g++) {
            
            // Acceder a la pieza actual del grid
            char **pieza_actual = piezas_grid[fila_g * col_grid + col_g]; 
            
            // Copiar los caracteres de la pieza al mapa final
            for (int i = 0; i < alto_pieza; i++) {
                for (int j = 0; j < ancho_pieza; j++) {
                    int pos_y_final = (fila_g * alto_pieza) + i;
                    int pos_x_final = (col_g * ancho_pieza) + j;
                    
                    mapa_final[pos_y_final][pos_x_final] = pieza_actual[i][j];
                }
            }
        }
    }
}

void colocar_inicio(char **mapa, Posicion inicio) {
    mapa[inicio.y][inicio.x] = 'I'; // O el caracter que uses para el inicio
}

void colocar_salida(char **mapa, Posicion salida) {
    mapa[salida.y][salida.x] = 'S';
}

void liberar_mapa(char **mapa, int filas) {
    if (mapa == NULL) return;
    for (int i = 0; i < filas; i++) {
        free(mapa[i]);
    }
    free(mapa);
}