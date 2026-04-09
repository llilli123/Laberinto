#ifndef JUGADOR_H
#define JUGADOR_H

// Estructura básica para manejar coordenadas
typedef struct {
    int x; // Columna
    int y; // Fila
} Posicion;

Posicion inicializar_jugador(int fila_inicio, int col_inicio);
int puede_moverse(char **mapa, int filas_mapa, int col_mapa, int nueva_fila, int nueva_col);
void mover_jugador(Posicion *jugador, char direccion, char **mapa, int filas_mapa, int col_mapa);
int llego_a_salida(Posicion jugador, Posicion salida);

#endif // JUGADOR_H