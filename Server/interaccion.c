//
// Created by alfab on 10/22/2020.
//
#include <stdio.h>
#include "windows.h"
#include "estructuras.h"
#include <unistd.h>
#include "interaccion.h"
char currentInstruction[COMMAND_LEN];
bool nuevoComando=false;
bool procesandoComando=false;
extern int terminate;


/**
 * Funcion que obtiene el comando del usuario y la guarda en una variable para ser leida por otro metodo
 * @return Retorna un valor usado por el thread que la ejecuta
 */
DWORD WINAPI updateInstruction(){
    while(!terminate) {
        if(!procesandoComando) {
            printf("\ncomando:");
            gets(currentInstruction);
            printf("\n");
            nuevoComando = true;
            procesandoComando=true;
        }
        sleep(1);
    }
    printf("");
}

/**
 * Funcion para eliminar del almacenamiento el comando anterior
 */
void cleanBuffer(){
    for(int i=0;i<COMMAND_LEN;i++){
        currentInstruction[i]='\0';
    }
}
/**
 * Funcion para leer el siguiente comando del usuario
 * @param dest Char en el cual se escribe el comando
 */
void getComando(char* dest){
    if(nuevoComando==true){
        strcpy(dest,currentInstruction);
        nuevoComando=false;
        cleanBuffer();
    }else{
        procesandoComando=false;
        strcpy(dest,"none ");
    }
}

/**
 * Funcion para iniciar la linea de comandos
 */
void iniciarInteraccion(){
    printf("Bienvenid@, administrad@r\n\n    Se ha iniciado el servidor\n");
    printf("    Se ha habilitado la linea de comandos\n");
    cleanBuffer();

    DWORD ThreadId;
    CreateThread(NULL, 0,  updateInstruction, NULL, 0, &ThreadId);
}