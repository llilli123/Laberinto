#include <stdio.h>
#include "validador.h"
#include "cola.h"

// Verifica si una posición está dentro del mapa
// f = fila, c = columna
int es_valida(int f, int c, int filas, int cols) {
    return f >= 0 && f < filas && c >= 0 && c < cols;
}

// Verifica si una celda se puede recorrer
// ' ' = camino libre
// 'E' = entrada
// 'S' = salida
int es_transitable(char c) {
    return c == ' ' || c == 'E' || c == 'S';
}

// Busca la entrada (E) y la salida (S) dentro del mapa
void buscar_puntos(char **mapa, int filas, int cols, Posicion *inicio, Posicion *salida) {

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {

            // Si encuentra la entrada, guarda su posición
            if (mapa[i][j] == 'E') {
                inicio->fila = i;
                inicio->col = j;
            }

            // Si encuentra la salida, guarda su posición
            if (mapa[i][j] == 'S') {
                salida->fila = i;
                salida->col = j;
            }
        }
    }
}

// BFS: busca camino usando una cola
int bfs_hay_camino(char **mapa, int filas, int cols) {

    Posicion inicio, salida;

    // Encontramos inicio y salida
    buscar_puntos(mapa, filas, cols, &inicio, &salida);

    // Matriz de visitados
    // 0 = no visitado, 1 = visitado
    int visitado[100][100] = {0};

    // Creamos la cola
    Cola cola;
    inicializar_cola(&cola);

    // Empezamos desde la entrada
    encolar(&cola, inicio);

    // Marcamos como visitada la posición inicial
    visitado[inicio.fila][inicio.col] = 1;

    // Movimientos posibles
    // arriba, abajo, izquierda, derecha
    int df[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // Mientras haya posiciones por explorar
    while (!cola_vacia(&cola)) {

        // Tomamos la posición actual
        Posicion actual = desencolar(&cola);

        // Si llegamos a la salida → hay camino
        if (actual.fila == salida.fila && actual.col == salida.col) {
            return 1;
        }

        // Revisamos las 4 direcciones
        for (int i = 0; i < 4; i++) {

            int nf = actual.fila + df[i];
            int nc = actual.col + dc[i];

            // Verificamos:
            // 1. Que esté dentro del mapa
            // 2. Que no haya sido visitado
            // 3. Que sea transitable
            if (es_valida(nf, nc, filas, cols) &&
                !visitado[nf][nc] &&
                es_transitable(mapa[nf][nc])) {

                // Marcamos como visitado
                visitado[nf][nc] = 1;

                // Lo agregamos a la cola
                Posicion siguiente = {nf, nc};
                encolar(&cola, siguiente);
            }
        }
    }

    // Si nunca se llegó a la salida, no hay camino
    return 0;
}