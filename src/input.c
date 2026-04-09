//
// Created by jorge on 4/8/2026.
//
#include <stdio.h>
#include <ctype.h>
#include "input.h"

#include <conio.h>   // IMPORTANTE

char leer_tecla(void) {
    return _getch(); // lee sin Enter
}

Accion convertir_tecla_a_movimiento(char tecla) {
    tecla = (char)tolower((unsigned char)tecla);

    switch (tecla) {
        case 'w':
            return ACCION_ARRIBA;
        case 's':
            return ACCION_ABAJO;
        case 'a':
            return ACCION_IZQUIERDA;
        case 'd':
            return ACCION_DERECHA;
        case 'q':
            return ACCION_SALIR;
        default:
            return ACCION_INVALIDA;
    }
}