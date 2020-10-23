//
// Created by alfab on 10/20/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"
#include "constants.h"

void agregarNodo(struct lista* lista, void* data){
    struct nodo* nuevoNodo=malloc(sizeof(struct nodo));
    *nuevoNodo=(struct nodo){data, NULL};
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

void* obtenerSiguiente(void* anterior, struct lista* lista){
    struct nodo* actualNodo=lista->primero;
    bool flag=1;
    while(actualNodo!=NULL && flag && anterior!=NULL){
        flag=actualNodo->data!=anterior;
        actualNodo=actualNodo->next;
    }
    return actualNodo==NULL? NULL : actualNodo->data;
}

void borrarUltimo(struct lista* lista){
    struct nodo* actualNodo=lista->primero;
    if(lista->primero!=NULL){
        if(lista->primero->next!=NULL) {
            while (actualNodo->next->next != NULL) {
                actualNodo = actualNodo->next;
            }
            free(actualNodo->next);
            actualNodo->next=NULL;
        }else{
            free(lista->primero);
            lista->primero=NULL;
        }
    }
}

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

struct ladrillo* obtenerLadrilloDestruido(int matriz[numFilas][numCol], struct lista listas[numFilas]){
    struct nodo* actualNodo;
    for(int i=0;i<numFilas;i++) {
        actualNodo=listas[i].primero;
        for(int j=0;j<numCol;j++) {
            if(((struct ladrillo*)actualNodo->data)->destruido!=matriz[i][j] && matriz[i][j]==1){
                return actualNodo->data;
            }
            actualNodo = actualNodo->next;
        }
    }
    return NULL;
}

bool quedanLadrillos(struct lista listas[numFilas]){
    struct nodo* actualNodo;
    for(int i=0;i<numFilas;i++) {
        actualNodo=listas[i].primero;
        for(int j=0;j<numCol;j++) {
            if(((struct ladrillo*)actualNodo->data)->destruido==false){
                return true;
            }
            actualNodo = actualNodo->next;
        }
    }
    return false;
}


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

void liberarLista(struct lista* lista)
{
    liberarListaAux(lista->primero);
}
