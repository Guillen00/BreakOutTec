//
// Created by alfab on 10/20/2020.
//
#include "estructuras.h"
#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H

int calcularLongitudAsString(int number);
int ladrilloToString(struct ladrillo* ladrillo, char* string);
int listaToChar(char* texto, struct lista* lista);
int listasToChar(char* texto);
int juegoToChar(char* texto,struct juego* juego);

#endif //SERVER_PARSER_H
