//
// Created by alfab on 10/20/2020.
//

#ifndef SERVER_ESTRUCTURAS_H
#define SERVER_ESTRUCTURAS_H

#include "constants.h"

/**
 * Se define el booleane
 */
typedef enum { false, true } bool;


/**
 * Se define la estructura tipo ladrillo
 */
struct ladrillo{
    int color;
    bool raquetaMitad;
    bool raquetaDoble;
    bool velocidadMas;
    bool velocidadMenos;
    bool vida;
    bool balon;
};


/**
 * Se define la estructura de nodo
 */
struct nodo{
    void* data;
    struct nodo* next;
};

/**
 * Se define la estructura de lista
 */
struct lista{
    struct nodo* primero;
};

/**
 * Se define a estructura juego que tiene todas las variables del juego
 */
struct juego{
    struct lista listas[8];
    char* url;
    int imagenumber;
    int puntaje;
    int record;
    int subirNivel;
    struct ladrillo* ladrillo;

    int puntajeVerde;
    int puntajeAmarillo;
    int puntajeNaranja;
    int puntajeRojo;

    int probRaqMitad;
    int probRaqDoble;

    int probVelMas;
    int probVelMenos;

    int probVida;
    int probBalon;
};

/**
 * Metodo para obtener el valor en la posicion indicada de una lista
 * @param lista Lista en la cual buscar
 * @param pos Posicion a buscar
 * @return Valor en la posicion buscada
 */
void* obtenerValor(struct lista* lista, int pos);
/**
 * Metodo para crear un ladrillo
 * @param color Color al que pertence el ladrillo
 * @param juego Estructura del juego actual
 * @return Retorna el ladrillo creado
 */
struct ladrillo* crearLadrillo(int color, struct juego* juego);

/**
 * Metodo para crear una fila del juego
 * @param color Color de la fila
 * @param juego Estructura actual del juego
 * @return Retorna una lista de ladrillos que representa la estructura actual del juego
 */
struct lista* crearFila(int color, struct juego* juego);

/**
 * Funcion para liberar la memoria de una lista
 * @param lista Lista a liberar
 */
void liberarLista(struct lista* lista);

#endif //SERVER_ESTRUCTURAS_H
