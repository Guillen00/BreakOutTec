//
// Created by alfab on 10/20/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "estructuras.h"
#include "parser.h"
#include "constants.h"
#include "socket.h"

struct juego juego={NULL,.vidas=vidaInicial,vidaInicial,1,0,NULL,0,1,
                    velocidadInicial,raquetaTamanoInicial,puntajeVerdeInicial,puntajeAmarilloInicial,
                    puntajeNaranjIniciala,puntajeRojoInicial,probRaqMitadinicial,
                    probRaqDobleinicial,probVelMasinicial,probVelMenosinicial,
                    probVidaInicial,probBalonInicial};

void nuevasListas(){
    struct lista* actual=juego.listas;
    for(int i=0;i<8;i++){
        *actual=*crearFila(i/2, &juego);
        actual++;
    }
}

void iniciarCoordenadas(){
    struct lista* lista=malloc(sizeof(struct lista));
    *lista=(struct lista){NULL};
    juego.coordenadasList=lista;
    struct lista* coords=juego.coordenadasList;
    struct coordenadas* coordenadas= malloc(sizeof(struct coordenadas));
    *coordenadas=(struct coordenadas){-1,-1};
    agregarNodo(coords,coordenadas);
}

void algoritmoDeCambioExponencial(){
    juego.probRaqMitad*=2;
    juego.probRaqDoble/=2;
    juego.probVelMas*=2;
    juego.probVelMenos/=2;
    juego.probVida/=2;
    juego.probBalon*=2;
    juego.velocidad*=1.3;
}


void subirPuntaje(int color){
    if(color==VERDE){
        juego.puntaje+=juego.puntajeVerde;
    }else if(color==AMARILLO){
        juego.puntaje+=juego.puntajeAmarillo;
    }else if(color==NARANJA){
        juego.puntaje+=juego.puntajeNaranja;
    }else if(color==ROJO){
        juego.puntaje+=juego.puntajeRojo;
    }
}

void ladrilloDestruido(struct ladrillo* ladrillo){
    ladrillo->destruido=true;
    if(ladrillo->velocidadMas){
        juego.velocidad*=1.3;
    }else if(ladrillo->velocidadMenos){
        juego.velocidad/=1.3;
    }
    if(ladrillo->raquetaDoble){
        juego.raquetaTamano*=2;
    }else if(ladrillo->raquetaMitad){
        juego.raquetaTamano/=2;
    }
    if(ladrillo->vida){
        juego.vidas++;
    }
    if(ladrillo->balon){
        juego.balones++;
        struct coordenadas* newcords=malloc(sizeof(struct coordenadas));
        *newcords=(struct coordenadas){-1,-1};
        agregarNodo(juego.coordenadasList,newcords);
    }
    subirPuntaje(ladrillo->color);
}

void reiniciarJuego(){
    juego=(struct juego){NULL,.vidas=vidaInicial,vidaInicial,1,0,
            (struct lista*){NULL},0,1,
           velocidadInicial,raquetaTamanoInicial,puntajeVerdeInicial,puntajeAmarilloInicial,
           puntajeNaranjIniciala,puntajeRojoInicial,probRaqMitadinicial,
           probRaqDobleinicial,probVelMasinicial,probVelMenosinicial,
           probVidaInicial,probBalonInicial};
    nuevasListas();
    iniciarCoordenadas();
}


void aumentarNivel(){
    algoritmoDeCambioExponencial();
    nuevasListas();
    iniciarCoordenadas();
    juego.balones=1;
    juego.nivel++;
}

void revisarLadrillos(int matriz[numFilas][numCol]){
    struct ladrillo *ladrillo = obtenerLadrilloDestruido(matriz, juego.listas);
    if(ladrillo!=NULL) {
        ladrilloDestruido(ladrillo);
    }
}

bool pasarNivel(){
    return !quedanLadrillos(juego.listas);
}

void revisarVida(){
    if(juego.vidas<juego.vidaAnterior){
        if(juego.balones>1){
            borrarUltimo(juego.coordenadasList);
        }
        juego.vidaAnterior=juego.vidas;
    }
}

void actualizarJuego(char* texto){
    _sleep(10);
    enviarDatos(texto);
    ///Se reciben los datos
    if(recibirDatos(texto)!=MESSAGE_ERROR){
        int matriz[numFilas][numCol];
        ///Se parsean los datos
        charToJuego(matriz,texto,&juego);
        ///Se actualizan los datos necesarios
        if(juego.vidas>0){
            revisarVida();
            if(!pasarNivel()){
                revisarLadrillos(matriz);
            }else{
                aumentarNivel();
            }
        }else{
            reiniciarJuego();
        }
        ///Se envian los datos
        juegoToChar(texto, &juego);
        enviarDatos(texto);
    }
}

_Noreturn void iniciar(){
    nuevasListas();
    iniciarCoordenadas();
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, (void *(*)(void *)) iniciarServer, NULL);

    bool flag=true;
    char texto[DEFAULT_BUFLEN];
    for(int i=0;i<DEFAULT_BUFLEN;i++){
        texto[i]='\0';
    }
    while(flag){
        actualizarJuego(texto);
    }
}