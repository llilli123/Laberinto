cmake_minimum_required(VERSION 4.2)
project(Laberinto C)

set(CMAKE_C_STANDARD 11)

add_executable(Laberinto src/main.c
        src/pieza.c
        src/catalogo_piezas.c
        src/generador.c
        src/mapa.c
        src/jugador.c
        src/cola.c
        src/pila.c
        src/lista.c
        src/validador.c
        src/render.c
        src/input.c
        src/juego.c
        src/ranking.c
        include/pieza.h
        include/catalogo_piezas.h
        include/generador.h
        include/mapa.h
        include/jugador.h
        include/cola.h
        include/pila.h
        include/lista.h
        include/validador.h
        include/render.h
        include/input.h
        include/juego.h
        include/ranking.h)
