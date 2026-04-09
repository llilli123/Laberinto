#include <stdio.h>
#include <string.h>
#include "pieza.h"

Pieza crear_pieza(const char *nombre,
                  const char forma[ALTO][ANCHO + 1],
                  int arriba, int abajo, int izquierda, int derecha) {
    Pieza p;
    int i;

    strncpy(p.nombre, nombre, sizeof(p.nombre) - 1);
    p.nombre[sizeof(p.nombre) - 1] = '\0';

    for (i = 0; i < ALTO; i++) {
        strncpy(p.forma[i], forma[i], ANCHO);
        p.forma[i][ANCHO] = '\0';
    }

    p.arriba = arriba;
    p.abajo = abajo;
    p.izquierda = izquierda;
    p.derecha = derecha;

    return p;
}

void copiar_pieza(Pieza *destino, const Pieza *origen) {
    if (destino && origen) {
        *destino = *origen;
    }
}

void imprimir_pieza(const Pieza *p) {
    if (!p) return;

    printf("Pieza: %s\n", p->nombre);
    printf("Puertas -> Arriba:%d Abajo:%d Izquierda:%d Derecha:%d\n",
           p->arriba, p->abajo, p->izquierda, p->derecha);

    for (int i = 0; i < ALTO; i++) {
        printf("%s\n", p->forma[i]);
    }
}

// Funciones de puertas
int tiene_puerta_arriba(const Pieza *p) { return p ? p->arriba : 0; }
int tiene_puerta_abajo(const Pieza *p) { return p ? p->abajo : 0; }
int tiene_puerta_izquierda(const Pieza *p) { return p ? p->izquierda : 0; }
int tiene_puerta_derecha(const Pieza *p) { return p ? p->derecha : 0; }