#include "jugador.h"
#include <ctype.h>

Posicion inicializar_jugador(int fila_inicio, int col_inicio) {
    Posicion p;
    p.y = fila_inicio;
    p.x = col_inicio;
    return p;
}

int puede_moverse(char **mapa, int filas_mapa, int col_mapa, int nueva_fila, int nueva_col) {
    // 1. Riesgo mitigado: No salir de los límites
    if (nueva_fila < 0 || nueva_fila >= filas_mapa || nueva_col < 0 || nueva_col >= col_mapa) {
        return 0; // Falso, fuera de límites
    }

    // 2. Riesgo mitigado: No pisar paredes
    char destino = mapa[nueva_fila][nueva_col];
    if (destino == ' ' || destino == 'S' || destino == '*') {
        return 1; // Verdadero, es transitable
    }

    return 0; // Falso, es pared ('#') u obstáculo
}

void mover_jugador(Posicion *jugador, char direccion, char **mapa, int filas_mapa, int col_mapa) {
    int nueva_fila = jugador->y;
    int nueva_col = jugador->x;

    // Convertir a mayúscula para aceptar tanto 'w' como 'W'
    switch(toupper(direccion)) {
        case 'W': nueva_fila--; break;
        case 'S': nueva_fila++; break;
        case 'A': nueva_col--; break;
        case 'D': nueva_col++; break;
        default: return; // Tecla no válida
    }

    if (puede_moverse(mapa, filas_mapa, col_mapa, nueva_fila, nueva_col)) {
        // Actualizar posición correctamente en la estructura
        jugador->y = nueva_fila;
        jugador->x = nueva_col;
    }
}

int llego_a_salida(Posicion jugador, Posicion salida) {
    return (jugador.x == salida.x && jugador.y == salida.y);
}