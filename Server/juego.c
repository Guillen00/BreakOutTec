//
// Created by alfab on 10/20/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"
#include "parser.h"
#include "constants.h"

struct juego juego={NULL,.vidas=vidaInicial,vidaInicial,1,0,(struct lista*){NULL},0,1,
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

void aumentarNivel(){
    algoritmoDeCambioExponencial();
    nuevasListas();
    iniciarCoordenadas();
    juego.balones=1;
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

void actualizarJuego(){
    char* mensajeRecibido="6;5;7\n4;2;3;4;5\n5;4;3;2;1\n0;0;0;0;0\n1;2;3;4;5\n5;4;3;2;1\n0;0;0;0;0\n1;0;1;0;1\n0;1;0;1;0\n";
    int matriz[numFilas][numCol];
    charToJuego(matriz,mensajeRecibido,&juego);
    struct ladrillo* ladrillo=obtenerLadrilloDestruido(matriz,  juego.listas);
    ladrilloDestruido(ladrillo);
}

void iniciar(){
    nuevasListas();
    iniciarCoordenadas();
    char texto[10000];
    juegoToChar(texto, &juego);
    printf("%s",texto);
    actualizarJuego();
    printf("%s","dd");
}

void reiniciarJuego(){
    juego.vidas = vidaInicial;
    juego.nivel= 1;
    juego.velocidad=velocidadInicial;

    juego.probRaqMitad=probRaqMitadinicial;
    juego.probRaqDoble=probRaqDobleinicial;

    juego.probVelMas=probVelMasinicial;
    juego.probVelMenos=probVelMenosinicial;

    juego.probVida=probVidaInicial;
    juego.probBalon=probBalonInicial;
}