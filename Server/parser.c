//
// Created by alfab on 10/20/2020.
//

#include <stdio.h>
#include "estructuras.h"
#include "constants.h"
#include <string.h>
#include <stdlib.h>

int calcularLongitudAsString(int number){
    return snprintf( NULL, 0, "%d", number )+1;
}
int ladrilloToString(struct ladrillo* ladrillo, char* string){
    char* index= string;
    sprintf(index, "%d;", ladrillo->destruido);
    index+=calcularLongitudAsString(ladrillo->destruido);
    return index-string;
}
int listaToChar(char* texto, struct lista* lista){
    struct nodo* actualNodo=lista->primero;
    char* index=texto;
    while(actualNodo!=NULL){
        index+=ladrilloToString(actualNodo->data,index);
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

int coordenadasToChar(char* texto, struct lista* lista){
    struct coordenadas* coords=obtenerSiguiente(NULL,lista);
    char * index=texto;
    while (coords!=NULL){
        sprintf(index, "%d;",coords->x);
        index+=calcularLongitudAsString(coords->x);
        if(obtenerSiguiente(coords,lista)!=NULL){
            sprintf(index, "%d;",coords->y);
        }else{
            sprintf(index, "%d\n",coords->y);
        }
        index+=calcularLongitudAsString(coords->y);
        coords=obtenerSiguiente(coords,lista);
    }
    return index-texto;
}

int juegoToChar(char* texto,struct juego* juego){
    char* index= texto;
    sprintf(index, "%d;",juego->vidas);
    index+=calcularLongitudAsString(juego->vidas);
    sprintf(index, "%d\n",juego->posicionRaqX);
    index+=calcularLongitudAsString(juego->posicionRaqX);
    sprintf(index, "%d;",juego->nivel);
    index+=calcularLongitudAsString(juego->nivel);
    sprintf(index, "%d;",juego->raquetaTamano);
    index+=calcularLongitudAsString(juego->raquetaTamano);
    sprintf(index, "%d;",juego->velocidad);
    index+=calcularLongitudAsString(juego->velocidad);
    sprintf(index, "%d;",juego->puntaje);
    index+=calcularLongitudAsString(juego->puntaje);
    sprintf(index, "%d\n",juego->balones);
    index+=calcularLongitudAsString(juego->balones);

    index+=coordenadasToChar(index, juego->coordenadasList);

    index+=listasToChar(index, juego);
    *index='\0';
    index++;
    return index-texto;
}

void actualizarValoresGenerales(char* texto,struct juego* juego){
    char * aux;
    char copyTexto[strlen(texto)];
    strcpy(copyTexto,texto);
    char * token = strtok_r(copyTexto, ";",&aux);
    juego->vidas=atoi(token);
    token = strtok_r(NULL, ";",&aux);
    juego->posicionRaqX=atoi(token);
}

void actualizarCoordenadas(char* texto,struct juego* juego){
    char * aux;
    char copyTexto[strlen(texto)];
    strcpy(copyTexto,texto);
    char * token = strtok_r(copyTexto, ";",&aux);

    struct coordenadas* coords=obtenerSiguiente(NULL,juego->coordenadasList);
    while (coords!=NULL && token!=NULL){
        coords->x=atoi(token);
        token = strtok_r(NULL, ";",&aux);
        coords->y = atoi(token);
        token = strtok_r(NULL, ";",&aux);
        coords = obtenerSiguiente(coords, juego->coordenadasList);
    }
}

void charToJuego(int matriz[numFilas][numCol],char* texto,struct juego* juego){
    char copyTexto[strlen(texto)];
    char* aux1;
    strcpy(copyTexto,texto);
    char * fila = strtok_r(copyTexto, "\n", &aux1);
    actualizarValoresGenerales(fila, juego);

    fila = strtok_r(NULL, "\n", &aux1);

    actualizarCoordenadas(fila, juego);

    fila = strtok_r(NULL, "\n", &aux1);

    for(int i =0;i<numFilas;i++) {
        char copyFila[strlen(fila)];
        char* aux2;
        strcpy(copyFila,fila);
        char* elemento = strtok_r(copyFila, ";",&aux2);
        for(int j=0; j<numCol;j++){
            matriz[i][j]=atoi(elemento);
            elemento = strtok_r(NULL, ";",&aux2);
            fila++;
        }
        fila = strtok_r(NULL, "\n",&aux1);
    }
}