#ifndef PIEZA_H
#define PIEZA_H

#define ALTO 3
#define ANCHO 3
#define MAX_PIEZAS 32

typedef struct {
    char nombre[40];
    char forma[ALTO][ANCHO + 1];
    int arriba;
    int abajo;
    int izquierda;
    int derecha;
} Pieza;

// Crear pieza
Pieza crear_pieza(const char *nombre,
                  const char forma[ALTO][ANCHO + 1],
                  int arriba, int abajo, int izquierda, int derecha);

// Copiar pieza
void copiar_pieza(Pieza *destino, const Pieza *origen);

// Imprimir pieza
void imprimir_pieza(const Pieza *p);

// Consultar puertas
int tiene_puerta_arriba(const Pieza *p);
int tiene_puerta_abajo(const Pieza *p);
int tiene_puerta_izquierda(const Pieza *p);
int tiene_puerta_derecha(const Pieza *p);

#endif