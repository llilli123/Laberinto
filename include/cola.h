#ifndef COLA_H
#define COLA_H

// Estructura que representa una posición en el mapa
// fila = fila del mapa
// col = columna del mapa
typedef struct {
    int fila;
    int col;
} Posicion;

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

// Inicializa la cola vacía
void inicializar_cola(Cola *c);

// Verifica si la cola está vacía
int cola_vacia(Cola *c);

// Inserta un elemento al final de la cola
void encolar(Cola *c, Posicion p);

// Saca el elemento del frente de la cola
Posicion desencolar(Cola *c);

#endif