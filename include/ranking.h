//
// Created by jorge on 4/8/2026.
//

#ifndef LABERINTO_RANKING_H
#define LABERINTO_RANKING_H

#define MAX_REGISTROS_RANKING 10
#define MAX_NOMBRE_JUGADOR 40

typedef struct {
    char nombre[MAX_NOMBRE_JUGADOR];
    int puntaje;
} RegistroRanking;

void ranking_inicializar(void);
void ranking_agregar(const char *nombre, int puntaje);
void ranking_mostrar(void);
int ranking_total_registros(void);

#endif //LABERINTO_RANKING_H
