cmake_minimum_required(VERSION 3.16)
project(Server C)

set(CMAKE_C_STANDARD 99)

add_executable(Server main.c main.h socket.c socket.h estructuras.c parser.c juego.c estructuras.h juego.h parser.h constants.h interaccion.c interaccion.h)
TARGET_LINK_LIBRARIES(Server ws2_32 )