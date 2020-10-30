//
// Created by alfab on 10/20/2020.
//


/**
 * A continuacion se define una serie de constantes del servidor
 */

#ifndef SERVER_CONSTANTS_H
#define SERVER_CONSTANTS_H

/**
 * Constantes internas de identificacion del color de un ladrillo
 */
#define VERDE 3
#define AMARILLO 2
#define NARANJA 1
#define ROJO 0


/**
 * Constantes que indican el numero de filas y de columnas del juego
 */
#define numCol 12
#define numFilas 8


/**
 * Puntajes en los ladrillos de cada color
 */
#define puntajeVerdeInicial 2
#define puntajeAmarilloInicial 10
#define puntajeNaranjIniciala 15
#define puntajeRojoInicial 20


/**
 * Probabilidades de que un ladrillo tenga alguna habilidad
 */
#define probRaqMitadinicial 15
#define probRaqDobleinicial 15
#define probVelMasinicial 15
#define probVelMenosinicial 15
#define probVidaInicial 15
#define probBalonInicial 15

/**
 * Se definen las constantes del servidor
 */
#define DEFAULT_BUFLEN 2048
#define DEFAULT_PORT "27015"
#define MAX_CLIENTS 10

#endif //SERVER_CONSTANTS_H
