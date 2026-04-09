#include "catalogo_piezas.h"

void cargar_catalogo_piezas(Pieza catalogo[], int *cantidad) {

    int i = 0;

    // 🔹 Pasillo horizontal
    const char ph[ALTO][ANCHO + 1] = {
        "#######",
        "#######",
        "       ",
        "#######",
        "#######"
    };
    catalogo[i++] = crear_pieza("Pasillo Horizontal", ph, 0, 0, 1, 1);

    // 🔹 Pasillo vertical
    const char pv[ALTO][ANCHO + 1] = {
        "### ###",
        "### ###",
        "### ###",
        "### ###",
        "### ###"
    };
    catalogo[i++] = crear_pieza("Pasillo Vertical", pv, 1, 1, 0, 0);

    // 🔹 Curva arriba-derecha
    const char cad[ALTO][ANCHO + 1] = {
        "### ###",
        "### ###",
        "      #",
        "###### ",
        "#######"
    };
    catalogo[i++] = crear_pieza("Curva Arriba-Derecha", cad, 1, 0, 0, 1);

    // 🔹 Curva arriba-izquierda
    const char cai[ALTO][ANCHO + 1] = {
        "### ###",
        "### ###",
        "#      ",
        " ######",
        "#######"
    };
    catalogo[i++] = crear_pieza("Curva Arriba-Izquierda", cai, 1, 0, 1, 0);

    // 🔹 Curva abajo-derecha
    const char cbd[ALTO][ANCHO + 1] = {
        "#######",
        "###### ",
        "      #",
        "### ###",
        "### ###"
    };
    catalogo[i++] = crear_pieza("Curva Abajo-Derecha", cbd, 0, 1, 0, 1);

    // 🔹 Curva abajo-izquierda
    const char cbi[ALTO][ANCHO + 1] = {
        "#######",
        " ######",
        "#      ",
        "### ###",
        "### ###"
    };
    catalogo[i++] = crear_pieza("Curva Abajo-Izquierda", cbi, 0, 1, 1, 0);

    // 🔹 Cruce (4 caminos)
    const char cruce[ALTO][ANCHO + 1] = {
        "### ###",
        "### ###",
        "       ",
        "### ###",
        "### ###"
    };
    catalogo[i++] = crear_pieza("Cruce", cruce, 1, 1, 1, 1);

    // 🔹 Callejón arriba
    const char ca[ALTO][ANCHO + 1] = {
        "### ###",
        "#######",
        "#######",
        "#######",
        "#######"
    };
    catalogo[i++] = crear_pieza("Callejon Arriba", ca, 1, 0, 0, 0);

    // 🔹 Callejón abajo
    const char cab[ALTO][ANCHO + 1] = {
        "#######",
        "#######",
        "#######",
        "#######",
        "### ###"
    };
    catalogo[i++] = crear_pieza("Callejon Abajo", cab, 0, 1, 0, 0);

    // 🔹 Inicio
    const char inicio[ALTO][ANCHO + 1] = {
        "#######",
        "#######",
        "E      ",
        "#######",
        "#######"
    };
    catalogo[i++] = crear_pieza("Inicio", inicio, 0, 0, 1, 1);

    // 🔹 Salida
    const char salida[ALTO][ANCHO + 1] = {
        "#######",
        "#######",
        "      S",
        "#######",
        "#######"
    };
    catalogo[i++] = crear_pieza("Salida", salida, 0, 0, 1, 1);

    *cantidad = i;
}