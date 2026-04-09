#include "catalogo_piezas.h"

void cargar_catalogo_piezas(Pieza catalogo[], int *cantidad) {
    int i = 0;

    /* =========================
       PASILLOS
       ========================= */

    const char horizontal[ALTO][ANCHO + 1] = {
        "###",
        "   ",
        "###"
    };
    catalogo[i++] = crear_pieza("Pasillo Horizontal", horizontal, 0, 0, 1, 1);

    const char vertical[ALTO][ANCHO + 1] = {
        "# #",
        "# #",
        "# #"
    };
    catalogo[i++] = crear_pieza("Pasillo Vertical", vertical, 1, 1, 0, 0);

    /* =========================
       CURVAS
       ========================= */

    const char curva_ar_der[ALTO][ANCHO + 1] = {
        "# #",
        "#  ",
        "###"
    };
    catalogo[i++] = crear_pieza("Curva Arriba-Derecha", curva_ar_der, 1, 0, 0, 1);

    const char curva_ar_izq[ALTO][ANCHO + 1] = {
        "# #",
        "  #",
        "###"
    };
    catalogo[i++] = crear_pieza("Curva Arriba-Izquierda", curva_ar_izq, 1, 0, 1, 0);

    const char curva_ab_der[ALTO][ANCHO + 1] = {
        "###",
        "#  ",
        "# #"
    };
    catalogo[i++] = crear_pieza("Curva Abajo-Derecha", curva_ab_der, 0, 1, 0, 1);

    const char curva_ab_izq[ALTO][ANCHO + 1] = {
        "###",
        "  #",
        "# #"
    };
    catalogo[i++] = crear_pieza("Curva Abajo-Izquierda", curva_ab_izq, 0, 1, 1, 0);

    /* =========================
       T
       ========================= */

    const char t_sin_arriba[ALTO][ANCHO + 1] = {
        "###",
        "   ",
        "# #"
    };
    catalogo[i++] = crear_pieza("T sin Arriba", t_sin_arriba, 0, 1, 1, 1);

    const char t_sin_abajo[ALTO][ANCHO + 1] = {
        "# #",
        "   ",
        "###"
    };
    catalogo[i++] = crear_pieza("T sin Abajo", t_sin_abajo, 1, 0, 1, 1);

    const char t_sin_izq[ALTO][ANCHO + 1] = {
        "# #",
        "#  ",
        "# #"
    };
    catalogo[i++] = crear_pieza("T sin Izquierda", t_sin_izq, 1, 1, 0, 1);

    const char t_sin_der[ALTO][ANCHO + 1] = {
        "# #",
        "  #",
        "# #"
    };
    catalogo[i++] = crear_pieza("T sin Derecha", t_sin_der, 1, 1, 1, 0);

    /* =========================
       CRUCE
       ========================= */

    const char cruce[ALTO][ANCHO + 1] = {
        "# #",
        "   ",
        "# #"
    };
    catalogo[i++] = crear_pieza("Cruce", cruce, 1, 1, 1, 1);

    /* =========================
       CALLEJONES
       ========================= */

    const char callejon_arriba[ALTO][ANCHO + 1] = {
        "# #",
        "###",
        "###"
    };
    catalogo[i++] = crear_pieza("Callejon Arriba", callejon_arriba, 1, 0, 0, 0);

    const char callejon_abajo[ALTO][ANCHO + 1] = {
        "###",
        "###",
        "# #"
    };
    catalogo[i++] = crear_pieza("Callejon Abajo", callejon_abajo, 0, 1, 0, 0);

    const char callejon_izquierda[ALTO][ANCHO + 1] = {
        "###",
        "  #",
        "###"
    };
    catalogo[i++] = crear_pieza("Callejon Izquierda", callejon_izquierda, 0, 0, 1, 0);

    const char callejon_derecha[ALTO][ANCHO + 1] = {
        "###",
        "#  ",
        "###"
    };
    catalogo[i++] = crear_pieza("Callejon Derecha", callejon_derecha, 0, 0, 0, 1);

    /* =========================
       ESPECIALES
       ========================= */



    *cantidad = i;
}