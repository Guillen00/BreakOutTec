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

void cleanBuffer(){
    for(int i=0;i<COMMAND_LEN;i++){
        currentInstruction[i]='\0';
    }
}

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

void iniciarInteraccion(){
    printf("Bienvenid@, administrad@r\n\n    Se ha iniciado el servidor\n");
    printf("    Se ha habilitado la linea de comandos\n");
    cleanBuffer();

    DWORD ThreadId;
    CreateThread(NULL, 0,  updateInstruction, NULL, 0, &ThreadId);
}