//
// Created by jorge on 4/8/2026.
//

#ifndef LABERINTO_INPUT_H
#define LABERINTO_INPUT_H

typedef enum {
    ACCION_INVALIDA = 0,
    ACCION_ARRIBA,
    ACCION_ABAJO,
    ACCION_IZQUIERDA,
    ACCION_DERECHA,
    ACCION_SALIR
} Accion;

char leer_tecla(void);
Accion convertir_tecla_a_movimiento(char tecla);

#endif //LABERINTO_INPUT_H
