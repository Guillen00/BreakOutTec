//
// Created by alfab on 10/20/2020.
//

#include <stdio.h>
#include "estructuras.h"
#include "constants.h"

int calcularLongitudAsString(int number){
    return snprintf( NULL, 0, "%d", number )+1;
}
int ladrilloToString(struct ladrillo* ladrillo, char* string){
    char* index= string;
    sprintf(index, "%d;", ladrillo->color);
    index+=calcularLongitudAsString(ladrillo->color);
    sprintf(index, "%d;", ladrillo->puntaje);
    index+=calcularLongitudAsString(ladrillo->puntaje);
    sprintf(index, "%d;", ladrillo->destruido);
    index+=calcularLongitudAsString(ladrillo->destruido);
    sprintf(index, "%d;", ladrillo->vida);
    index+=calcularLongitudAsString(ladrillo->vida);
    sprintf(index, "%d;", ladrillo->balon);
    index+=calcularLongitudAsString(ladrillo->balon);
    sprintf(index, "%d;", ladrillo->raquetaDoble);
    index+=calcularLongitudAsString(ladrillo->raquetaDoble);
    sprintf(index, "%d;", ladrillo->raquetaMitad);
    index+=calcularLongitudAsString(ladrillo->raquetaMitad);
    sprintf(index, "%d;", ladrillo->velocidadMas);
    index+=calcularLongitudAsString(ladrillo->velocidadMas);
    sprintf(index, "%d-", ladrillo->velocidadMenos);
    index+=calcularLongitudAsString(ladrillo->velocidadMenos);
    return index-string;
}
int listaToChar(char* texto, struct lista* lista){
    struct nodo* actualNodo=lista->primero;
    char* index=texto;
    while(actualNodo!=NULL){
        index+=ladrilloToString(actualNodo->ladrillo,index);
        actualNodo=actualNodo->next;
    }
    return index-texto;
}
int listasToChar(char* texto, struct juego* juego){
    char* index=texto;
    int length;
    for(int i=0; i<numFilas;i++){
        length=listaToChar(index,&juego->listas[i]);
        index+=length;
        *index='\n';
        index++;
    }
    return index-texto;
}

int juegoToChar(char* texto,struct juego* juego){
    char* index= texto;
    sprintf(index, "%d;",juego->vidas);
    index+=calcularLongitudAsString(juego->vidas);
    sprintf(index, "%d;",juego->nivel);
    index+=calcularLongitudAsString(juego->nivel);
    sprintf(index, "%d;",juego->velocidad);
    index+=calcularLongitudAsString(juego->velocidad);
    sprintf(index, "%d;",juego->posicionX);
    index+=calcularLongitudAsString(juego->posicionX);
    sprintf(index, "%d\n",juego->posicionY);
    index+=calcularLongitudAsString(juego->posicionY);
    index+=listasToChar(index, juego);
    *index='\0';
    index++;
    return index-texto;
}