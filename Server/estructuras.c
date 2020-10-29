//
// Created by alfab on 10/20/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"
#include "constants.h"
/**
 * Metodo para obtener el valor en la posicion indicada de una lista
 * @param lista Lista en la cual buscar
 * @param pos Posicion a buscar
 * @return Valor en la posicion buscada
 */
void* obtenerValor(struct lista* lista, int pos){
    struct nodo* actualNodo=lista->primero;
    for(int i=0;i<pos;i++) {
        if(actualNodo==NULL){
            break;
        }
        actualNodo = actualNodo->next;
    }
    return actualNodo->data;
}
/**
 * Metodo para crear un ladrillo
 * @param color Color al que pertence el ladrillo
 * @param juego Estructura del juego actual
 * @return Retorna el ladrillo creado
 */
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
}

/**
 * Metodo para crear una fila del juego
 * @param color Color de la fila
 * @param juego Estructura actual del juego
 * @return Retorna una lista de ladrillos que representa la estructura actual del juego
 */
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

/**
 * Funcion auxiliar para liberar la memoria de una lista
 * @param lista Lista a liberar
 */
void liberarListaAux(struct nodo* cabeza)
{
    struct nodo* tmp;
    while (cabeza != NULL)
    {
        tmp = cabeza;
        cabeza = cabeza->next;
        free(tmp);
    }
}
/**
 * Funcion para liberar la memoria de una lista
 * @param lista Lista a liberar
 */
void liberarLista(struct lista* lista)
{
    liberarListaAux(lista->primero);
}
