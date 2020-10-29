//
// Created by alfab on 10/20/2020.
//
#include "estructuras.h"
#include "constants.h"
#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H

/**
 * Metodo auxiliar para calcular la longitud de un numero como string
 * @param number Numero al cual calcular la longitud
 * @return Longitud en chars del numero
 */
int calcularLongitudAsString(int number);
/**
 * Metodo para convertir los estados del juego en un texto
 * @param texto Estados del juego parseados
 * @param juego Estructura de datos del juego
 * @return Entero que indica el tamano del texto parseado
 */
int juegoToChar(char* texto,struct juego* juego);
/**
 * Metodo para parsear un texto a las variables de juego
 * @param texto Texto con la informacion nueva
 * @param juego Estructura de juego actual
 */
void charToJuego(char* texto,struct juego* juego);
#endif //SERVER_PARSER_H
