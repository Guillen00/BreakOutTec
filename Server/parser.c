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

int juegoToChar(char* texto,struct juego* juego){
    char* index= texto;

    strcpy(index,juego->url);
    index+=strlen(juego->url);
    *index=';';
    index++;
    sprintf(index, "%d;", juego->puntaje);
    index += calcularLongitudAsString(juego->puntaje);

    struct ladrillo* ladrillo=juego->ladrillo;

    if(ladrillo!=NULL) {
        sprintf(index, "%d;", ladrillo->raquetaMitad);
        index += calcularLongitudAsString(ladrillo->raquetaMitad);
        sprintf(index, "%d;", ladrillo->raquetaDoble);
        index += calcularLongitudAsString(ladrillo->raquetaDoble);
        sprintf(index, "%d;", ladrillo->velocidadMas);
        index += calcularLongitudAsString(ladrillo->velocidadMas);
        sprintf(index, "%d;", ladrillo->velocidadMenos);
        index += calcularLongitudAsString(ladrillo->velocidadMenos);
        sprintf(index, "%d;", ladrillo->vida);
        index += calcularLongitudAsString(ladrillo->vida);
        sprintf(index, "%d", ladrillo->balon);
        index += calcularLongitudAsString(ladrillo->balon);
        *(index-1)='\n';
    }else{
        strcpy(index,"0;0;0;0;0;0");
        index+=11;
        *index='\n';
    }
    return index-texto;
}

void charToJuego(char* texto,struct juego* juego){
    char copyTexto[strlen(texto)];
    char* aux1;
    strcpy(copyTexto,texto);

    char * token = strtok_r(copyTexto, ";", &aux1);
    strcpy(juego->url,token);

    token = strtok_r(NULL, ";", &aux1);
    juego->subirNivel=atoi(token);

    token = strtok_r(NULL, ";", &aux1);
    int columna= atoi(token);

    token = strtok_r(NULL, ";", &aux1);
    int fila= atoi(token);

    if(columna>=0 && fila>=0){
        juego->ladrillo=obtenerValor(&juego->listas[fila],columna);
    }
}