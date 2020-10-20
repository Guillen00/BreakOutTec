//
// Created by alfab on 10/20/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"
#include "constants.h"

void agregarNodo(struct lista* lista, struct ladrillo* ladrillo){
    struct nodo* nuevoNodo=malloc(sizeof(struct nodo));
    *nuevoNodo=(struct nodo){ladrillo, NULL};
    struct nodo* actualNodo=lista->primero;

    if (lista->primero==NULL){
        lista->primero= nuevoNodo;
    }else{
        while(actualNodo->next!=NULL){
            actualNodo=actualNodo->next;
        }
        actualNodo->next=nuevoNodo;
    }
}
struct nodo* obtenerNodo(struct lista* lista, int pos){
    struct nodo* actualNodo=lista->primero;
    for(int i=0;i<pos;i++) {
        if(actualNodo==NULL){
            break;
        }
        actualNodo = actualNodo->next;
    }
    return actualNodo;
}
struct ladrillo* crearLadrillo(int color, struct juego* juego){
    struct ladrillo* ladrillo=malloc(sizeof(struct ladrillo));
    ladrillo->color=color;

    ladrillo->raquetaDoble=rand() % 100<juego->probRaqDoble;
    if(ladrillo->raquetaDoble==false){
        ladrillo->raquetaMitad=rand() % 100<juego->probRaqMitad;
    }else{
        ladrillo->raquetaMitad=false;
    }

    ladrillo->velocidadMas=rand() % 100<juego->probVelMas;
    if(ladrillo->velocidadMas==false){
        ladrillo->velocidadMenos=rand() % 100<juego->probVelMenos;
    }else {
        ladrillo->velocidadMenos = false;
    }

    ladrillo->balon=rand() % 100<juego->probBalon;
    ladrillo->vida=rand() % 100<juego->probVida;
    ladrillo->destruido=false;

    if(color==VERDE){
        ladrillo->puntaje=puntajeVerde;
    }else if(color==AMARILLO){
        ladrillo->puntaje=puntajeAmarillo;
    }else if(color==NARANJA){
        ladrillo->puntaje=puntajeNaranja;
    }else if(color==ROJO){
        ladrillo->puntaje=puntajeRojo;
    }
}
struct lista* crearFila(int color, struct juego* juego){
    struct lista* lista=malloc(sizeof(struct lista));
    struct nodo* nuevoNodo=malloc(sizeof(struct nodo));
    struct ladrillo* ladrillo=crearLadrillo(color, juego);
    *nuevoNodo=(struct nodo){ladrillo,NULL};
    lista->primero=nuevoNodo;
    struct nodo* actualNodo=lista->primero;

    for(int i=1;i<numCol;i++){
        nuevoNodo=malloc(sizeof(struct nodo));
        ladrillo=crearLadrillo(color, juego);
        *nuevoNodo=(struct nodo){ladrillo,NULL};
        actualNodo->next=nuevoNodo;
        actualNodo=nuevoNodo;
    }
    return lista;
}

