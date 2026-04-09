#ifndef MAPA_H
#define MAPA_H
#include "jugador.h"

char **crear_mapa(int filas, int columnas);
// Asumimos que piezas_grid es una matriz 2D que contiene las sub-matrices (piezas)
void ensamblar_mapa(char **mapa_final, char ***piezas_grid, int filas_grid, int col_grid, int alto_pieza, int ancho_pieza);
void colocar_inicio(char **mapa, Posicion inicio);
void colocar_salida(char **mapa, Posicion salida);
void liberar_mapa(char **mapa, int filas);

#endif // MAPA_H