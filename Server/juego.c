//
// Created by alfab on 10/20/2020.
//
#include <stdio.h>
#include "estructuras.h"
#include "parser.h"
#include "constants.h"

struct juego juego={NULL,.vidas=vidaInicial,1,0,0,velocidadInicial,probRaqMitadinicial,
                    probRaqDobleinicial,probVelMasinicial,probVelMenosinicial,probVidaInicial,probBalonInicial};


void actualizarListas(){
    struct lista* actual=juego.listas;
    for(int i=0;i<8;i++){
        *actual=*crearFila(i/2, &juego);
        actual++;
    }
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
    actualizarListas();
}
void iniciar(){
    actualizarListas();
    char texto[10000];
    juegoToChar(texto, &juego);
    printf("%s",texto);
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