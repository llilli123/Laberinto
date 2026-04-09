#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Nodo *crear_nodo(const char *nombre, char simbolo, int cantidad) {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));

    if (nuevo == NULL) {
        printf("Error: no se pudo asignar memoria\n");
        return NULL;
    }

    strcpy(nuevo->nombre, nombre);
    nuevo->simbolo = simbolo;
    nuevo->cantidad = cantidad;
    nuevo->sig = NULL;

    return nuevo;
}

void insertar_item(Nodo **cabeza, const char *nombre, char simbolo, int cantidad) {
    Nodo *nuevo = crear_nodo(nombre, simbolo, cantidad);

    if (nuevo == NULL) return;

    Nodo *actual = *cabeza;
    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) {
            actual->cantidad += cantidad;
            free(nuevo);
            return;
        }
        actual = actual->sig;
    }

    nuevo->sig = *cabeza;
    *cabeza = nuevo;
}

void mostrar_inventario(Nodo *cabeza) {
    if (cabeza == NULL) {
        printf("Inventario vacio\n");
        return;
    }

    Nodo *actual = cabeza;

    printf("=== INVENTARIO ===\n");
    while (actual != NULL) {
        printf("Nombre: %s | Simbolo: %c | Cantidad: %d\n",
               actual->nombre,
               actual->simbolo,
               actual->cantidad);
        actual = actual->sig;
    }
}

int buscar_item(Nodo *cabeza, const char *nombre) {
    Nodo *actual = cabeza;

    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) {
            return 1;
        }
        actual = actual->sig;
    }

    return 0;
}

void liberar_lista(Nodo **cabeza) {
    Nodo *actual = *cabeza;
    Nodo *temp;

    while (actual != NULL) {
        temp = actual;
        actual = actual->sig;
        free(temp);
    }

    *cabeza = NULL;
}