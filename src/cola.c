#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

// Inicializa la cola
// Al inicio no hay elementos, por eso frente y final son NULL
void inicializar_cola(Cola *c) {
    c->frente = NULL;
    c->final = NULL;
}

// Verifica si la cola está vacía
// Si frente es NULL, no hay elementos
int cola_vacia(Cola *c) {
    return c->frente == NULL;
}


// Inserta una posición al final de la cola
void encolar(Cola *c, Posicion p) {

    // Se crea un nuevo nodo en memoria dinámica
    Nodo *nuevo = (Nodo*) malloc(sizeof(Nodo));

    // Si falla la memoria, mostramos error
    if (nuevo == NULL) {
        printf("Error de memoria\n");
        return;
    }

    // Guardamos la posición en el nodo
    nuevo->dato = p;

    // Como será el último nodo, no apunta a nada
    nuevo->siguiente = NULL;

    // Si la cola está vacía
    if (c->final == NULL) {
        // El nuevo nodo es el primero y último
        c->frente = nuevo;
        c->final = nuevo;
    } else {
        // El último nodo actual apunta al nuevo
        c->final->siguiente = nuevo;

        // El nuevo nodo pasa a ser el último
        c->final = nuevo;
    }
}

// Saca el elemento del frente de la cola
Posicion desencolar(Cola *c) {

    // Posición inválida en caso de error
    Posicion invalido = {-1, -1};

    // Si la cola está vacía, no hay nada que sacar
    if (cola_vacia(c)) {
        return invalido;
    }

    // Guardamos el nodo del frente
    Nodo *temp = c->frente;

    // Guardamos el dato para devolverlo
    Posicion dato = temp->dato;

    // Movemos el frente al siguiente nodo
    c->frente = temp->siguiente;

    // Si la cola quedó vacía, también final debe ser NULL
    if (c->frente == NULL) {
        c->final = NULL;
    }

    // Liberamos el nodo anterior
    free(temp);



    return dato;
}

void liberar_cola(Cola *c) {
    while (!cola_vacia(c)) {
        desencolar(c);
    }
}