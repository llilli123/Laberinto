//
// Created by jorge on 4/8/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include "render.h"

void limpiar_pantalla(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void mostrar_menu(void) {
    printf("=====================================\n");
    printf("         LABERINTO EN CONSOLA        \n");
    printf("=====================================\n");
    printf("Controles del juego:\n");
    printf("  W -> Mover arriba\n");
    printf("  S -> Mover abajo\n");
    printf("  A -> Mover izquierda\n");
    printf("  D -> Mover derecha\n");
    printf("  Q -> Salir del juego\n");
    printf("=====================================\n");
}

void dibujar_mapa(char mapa[][100], int filas, int columnas) {
    int i, j;

    printf("\nMAPA DEL JUEGO\n");
    printf("-------------------------------------\n");

    for (i = 0; i < filas; i++) {
        for (j = 0; j < columnas; j++) {
            printf("%c ", mapa[i][j]);
        }
        printf("\n");
    }

    printf("-------------------------------------\n");
}

void mostrar_estado(int vidas, int puntaje, const char *mensaje) {
    printf("\nESTADO DEL JUGADOR\n");
    printf("Vidas   : %d\n", vidas);
    printf("Puntaje : %d\n", puntaje);

    if (mensaje != NULL) {
        printf("Mensaje : %s\n", mensaje);
    }
}

void mostrar_mensaje(const char *mensaje) {
    if (mensaje != NULL) {
        printf("\n%s\n", mensaje);
    }
}

void mostrar_victoria(void) {
    printf("\n=====================================\n");
    printf("            ¡VICTORIA!               \n");
    printf("   Has completado el laberinto.      \n");
    printf("=====================================\n");
}

void mostrar_derrota(void) {
    printf("\n=====================================\n");
    printf("             GAME OVER               \n");
    printf("      El jugador ha sido derrotado.  \n");
    printf("=====================================\n");
}

void mostrar_leyenda(void) {
    printf("\nLEYENDA DEL MAPA\n");
    printf("J = Jugador\n");
    printf("E = Entrada o inicio\n");
    printf("S = Salida\n");
    printf("# = Muro\n");
    printf(". = Camino libre\n");
    printf("* = Objeto / premio / trampa\n");
}