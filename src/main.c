#include <stdio.h>
#include "juego.h"

int main(void) {
    if (!juego_init()) {
        printf("Error: no se pudo inicializar el juego.\n");
        printf("Presiona ENTER para salir...");
        getchar();
        return 1;
    }

    juego_run();
    juego_cleanup();

    printf("\nPresiona ENTER para cerrar...");
    getchar();
    getchar();

    return 0;
}