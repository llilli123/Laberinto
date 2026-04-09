#ifndef MAPA_H
#define MAPA_H
#include "jugador.h"
#include "generador.h"
#include "posicion.h"

char **crear_mapa(int filas, int columnas);
// Asumimos que piezas_grid es una matriz 2D que contiene las sub-matrices (piezas)
void ensamblar_mapa_desde_grid(Pieza grid[GRID_FILAS][GRID_COLS],
                               char mapa[][100],
                               int filas_mapa,
                               int cols_mapa);
void colocar_inicio(char **mapa, Posicion inicio);
void colocar_salida(char **mapa, Posicion salida);
void liberar_mapa(char **mapa, int filas);

#endif // MAPA_H