//
// Created by jorge on 4/8/2026.
//

#ifndef LABERINTO_LISTA_H
#define LABERINTO_LISTA_H

typedef struct Nodo {
    char nombre[30];
    char simbolo;
    int cantidad;
    struct Nodo *sig;
} Nodo;


Nodo *crear_nodo(const char *nombre, char simbolo, int cantidad);
void insertar_item(Nodo **cabeza, const char *nombre, char simbolo, int cantidad);
void mostrar_inventario(Nodo *cabeza);
int buscar_item(Nodo *cabeza, const char *nombre);
void liberar_lista(Nodo **cabeza);

#endif //LABERINTO_LISTA_H
