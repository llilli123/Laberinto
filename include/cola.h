#ifndef COLA_H
#define COLA_H

#include "posicion.h"

// Nodo de la cola
// Guarda una posición y un puntero al siguiente nodo
typedef struct Nodo {
    Posicion dato;
    struct Nodo *siguiente;
} Nodo;

// Estructura principal de la cola
// frente = primer elemento en salir
// final = último elemento insertado
typedef struct {
    Nodo *frente;
    Nodo *final;
} Cola;

void liberar_cola(Cola *c);
// Inicializa la cola vacía
void inicializar_cola(Cola *c);

// Verifica si la cola está vacía
int cola_vacia(Cola *c);

// Inserta un elemento al final de la cola
void encolar(Cola *c, Posicion p);

// Saca el elemento del frente de la cola
Posicion desencolar(Cola *c);

#endif