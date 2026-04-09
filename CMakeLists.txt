cmake_minimum_required(VERSION 3.10)  # 4.2 no es estándar aún
project(Laberinto C)

set(CMAKE_C_STANDARD 11)

add_executable(Laberinto
        src/main.c
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
)

# 🔥 AQUÍ está la clave
target_include_directories(Laberinto PRIVATE include)