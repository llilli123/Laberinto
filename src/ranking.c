#include <stdio.h>
#include <string.h>
#include "ranking.h"

static RegistroRanking ranking[MAX_REGISTROS_RANKING];
static int total_registros = 0;

static void ordenar_ranking_descendente(void) {
    int i, j;

    for (i = 0; i < total_registros - 1; i++) {
        for (j = i + 1; j < total_registros; j++) {
            if (ranking[j].puntaje > ranking[i].puntaje) {
                RegistroRanking temp = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = temp;
            }
        }
    }
}

void ranking_inicializar(void) {
    total_registros = 0;
}

void ranking_agregar(const char *nombre, int puntaje) {
    if (nombre == NULL) {
        return;
    }

    if (total_registros < MAX_REGISTROS_RANKING) {
        strncpy(ranking[total_registros].nombre, nombre, MAX_NOMBRE_JUGADOR - 1);
        ranking[total_registros].nombre[MAX_NOMBRE_JUGADOR - 1] = '\0';
        ranking[total_registros].puntaje = puntaje;
        total_registros++;
    } else {
        ordenar_ranking_descendente();

        if (puntaje > ranking[total_registros - 1].puntaje) {
            strncpy(ranking[total_registros - 1].nombre, nombre, MAX_NOMBRE_JUGADOR - 1);
            ranking[total_registros - 1].nombre[MAX_NOMBRE_JUGADOR - 1] = '\0';
            ranking[total_registros - 1].puntaje = puntaje;
        }
    }

    ordenar_ranking_descendente();
}

void ranking_mostrar(void) {
    int i;

    printf("\n=========== RANKING ===========\n");

    if (total_registros == 0) {
        printf("No hay puntajes registrados.\n");
        printf("===============================\n");
        return;
    }

    for (i = 0; i < total_registros; i++) {
        printf("%d. %s -> %d puntos\n", i + 1, ranking[i].nombre, ranking[i].puntaje);
    }

    printf("===============================\n");
}

int ranking_total_registros(void) {
    return total_registros;
}