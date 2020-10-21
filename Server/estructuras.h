//
// Created by alfab on 10/20/2020.
//

#ifndef SERVER_ESTRUCTURAS_H
#define SERVER_ESTRUCTURAS_H

#include "constants.h"

typedef enum { false, true } bool;



struct ladrillo{
    int color;
    bool raquetaMitad;
    bool raquetaDoble;
    bool velocidadMas;
    bool velocidadMenos;
    bool vida;
    bool balon;
    bool destruido;
};

struct coordenadas{
    int x;
    int y;
};

struct nodo{
    void* data;
    struct nodo* next;
};
struct lista{
    struct nodo* primero;
};
struct juego{
    struct lista listas[8];
    int vidas;
    int vidaAnterior;
    int nivel;
    int posicionRaqX;
    struct lista* coordenadasList;
    int puntaje;
    int balones;
    int velocidad;

    int raquetaTamano;

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

void agregarNodo(struct lista* lista, void* data);
void* obtenerSiguiente(void* anterior, struct lista* lista);
struct nodo* obtenerNodo(struct lista* lista, int pos);
struct ladrillo* crearLadrillo(int color, struct juego* juego);
struct lista* crearFila(int color, struct juego* juego);
struct ladrillo* obtenerLadrilloDestruido(int matriz[numFilas][numCol], struct lista listas[numFilas] );
void borrarUltimo(struct lista* lista);
bool quedanLadrillos(struct lista listas[numFilas]);
#endif //SERVER_ESTRUCTURAS_H
