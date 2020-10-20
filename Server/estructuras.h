//
// Created by alfab on 10/20/2020.
//

#ifndef SERVER_ESTRUCTURAS_H
#define SERVER_ESTRUCTURAS_H

typedef enum { false, true } bool;
struct ladrillo{
    int color;
    int puntaje;
    bool raquetaMitad;
    bool raquetaDoble;
    bool velocidadMas;
    bool velocidadMenos;
    bool vida;
    bool balon;
    bool destruido;
};
struct nodo{
    struct ladrillo* ladrillo;
    struct nodo* next;
};
struct lista{
    struct nodo* primero;
};
struct juego{
    struct lista listas[8];
    int vidas;
    int nivel;
    int posicionX;
    int posicionY;

    int velocidad;

    int probRaqMitad;
    int probRaqDoble;

    int probVelMas;
    int probVelMenos;

    int probVida;
    int probBalon;
};

void agregarNodo(struct lista* lista, struct ladrillo* ladrillo);
struct nodo* obtenerNodo(struct lista* lista, int pos);
struct ladrillo* crearLadrillo(int color, struct juego* juego);
struct lista* crearFila(int color, struct juego* juego);


#endif //SERVER_ESTRUCTURAS_H
