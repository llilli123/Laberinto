//
// Created by jorge on 4/8/2026.
//

#ifndef LABERINTO_RENDER_H
#define LABERINTO_RENDER_H

void limpiar_pantalla(void);
void mostrar_menu(void);
void dibujar_mapa(char mapa[][100], int filas, int columnas);
void mostrar_estado(int vidas, int puntaje, const char *mensaje);
void mostrar_mensaje(const char *mensaje);
void mostrar_victoria(void);
void mostrar_derrota(void);
void mostrar_leyenda(void);

#endif //LABERINTO_RENDER_H
