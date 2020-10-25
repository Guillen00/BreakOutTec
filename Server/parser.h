//
// Created by alfab on 10/20/2020.
//
#include "estructuras.h"
#include "constants.h"
#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H


int calcularLongitudAsString(int number);
int juegoToChar(char* texto,struct juego* juego);
void charToJuego(char* texto,struct juego* juego);
#endif //SERVER_PARSER_H
