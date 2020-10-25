//
// Created by alfab on 10/20/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "parser.h"
#include "constants.h"
#include "socket.h"
#include "interaccion.h"
#include "windows.h"
struct juego juego={NULL,.vidas=vidaInicial,vidaInicial,1,0,numCol,NULL,0,1,
                    velocidadInicial,raquetaTamanoInicial,puntajeVerdeInicial,puntajeAmarilloInicial,
                    puntajeNaranjIniciala,puntajeRojoInicial,probRaqMitadinicial,
                    probRaqDobleinicial,probVelMasinicial,probVelMenosinicial,
                    probVidaInicial,probBalonInicial};

int terminate=0;

void liberarListasIntermedio(){
    liberarLista(juego.coordenadasList);
    for(int i=0;i<numFilas;i++) {
        liberarLista(&juego.listas[i]);
    }
}

void nuevasListas(){
    for(int i=0;i<8;i++){
        juego.listas[i]=*crearFila(i/2, &juego);
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
    }
    if(ladrillo->velocidadMenos){
        juego.velocidad/=1.3;
    }
    if(ladrillo->raquetaDoble){
        juego.raquetaTamano*=2;
    }
    if(ladrillo->raquetaMitad){
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
    liberarListasIntermedio();
    juego=(struct juego){NULL,.vidas=vidaInicial,vidaInicial,1,0,numCol,
            (struct lista*){NULL},0,1,
           velocidadInicial,raquetaTamanoInicial,puntajeVerdeInicial,puntajeAmarilloInicial,
           puntajeNaranjIniciala,puntajeRojoInicial,probRaqMitadinicial,
           probRaqDobleinicial,probVelMasinicial,probVelMenosinicial,
           probVidaInicial,probBalonInicial};
    nuevasListas();
    iniciarCoordenadas();
}


void aumentarNivel(){
    liberarListasIntermedio();
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
    if(isJugadorActivo()) {
        juegoToChar(texto, &juego);
        enviarDatos(texto);
        ///Se reciben los datos
        if (recibirDatos(texto) != MESSAGE_ERROR) {
            int matriz[numFilas][numCol];
            ///Se parsean los datos
            charToJuego(matriz, texto, &juego);
            ///Se actualizan los datos necesarios
            if (juego.vidas > 0) {
                revisarVida();
                if (!pasarNivel()) {
                    revisarLadrillos(matriz);
                } else {
                    aumentarNivel();
                }
            } else {
                reiniciarJuego();
            }
        }
    }
}

void checkearLadrillosAdministradorA(char* setget, int* exito, bool setCorrecto, char* texto,
                                                int valorNuevo, bool *valor, bool* valorOpuesto){
    if (strcmp(setget, "set") == 0) {
        if (setCorrecto) {
            *valor = valorNuevo;
            if (valorNuevo) {
                *valorOpuesto = 0;
            }
            *exito = true;
        }
    } else {
        printf(*valor ? "%s: true\n" : "%s: false\n",texto);
        *exito = true;
    }
}

void checkearPuntajesAdministrador(char* setget, int number, int* exito, char* texto, int* valor){
    if(strcmp(setget,"set")==0) {
        if(number>0){
            *valor = number;
            *exito=true;
        }
    }else{
        printf("%s: %d\n",texto,*valor);
        *exito=true;
    }
}

void actualizacionDeAdministrador(){
    char comando[COMMAND_LEN];
    char* token;
    getComando(comando);
    char* setget=strtok(comando, " ");
    token=strtok(NULL, " ");
    int exito=false;
    if(token!=NULL && setget!=NULL) {
        if (strcmp(setget, "set") == 0 || strcmp(setget, "get") == 0) {
            if (strcmp(token, "puntuacion") == 0) {
                token = strtok(NULL, " ");
                int number = atoi(strtok(NULL, " "));
                if (strcmp(token, "verde") == 0) {
                    checkearPuntajesAdministrador(setget, number, &exito, "Puntaje Verde", &juego.puntajeVerde);
                } else if (strcmp(token, "amarillo") == 0) {
                    checkearPuntajesAdministrador(setget, number, &exito, "Puntaje Amarillo", &juego.puntajeAmarillo);
                } else if (strcmp(token, "naranja") == 0) {
                    checkearPuntajesAdministrador(setget, number, &exito, "Puntaje Naranja", &juego.puntajeNaranja);
                } else if (strcmp(token, "rojo") == 0) {
                    checkearPuntajesAdministrador(setget, number, &exito, "Puntaje Rojo", &juego.puntajeRojo);
                }
            } else if (strcmp(token, "ladrillo") == 0) {
                int number1 = atoi(strtok(NULL, " "));
                int number2 = atoi(strtok(NULL, " "));

                token = strtok(NULL, " ");
                char *booleano = strtok(NULL, " ");
                bool numericosCorrectos = number1 > 0 && number2 > 0 && number1 < 9 && number2 < (juego.numeroCol + 1);

                if (numericosCorrectos && token != NULL) {
                    struct ladrillo *ladrillo = ((struct ladrillo *) obtenerValor(&juego.listas[number1 - 1],
                                                                                  number2 - 1));

                    bool valor;
                    bool setCorrecto = false;

                    if (booleano != NULL) {
                        valor = (strcmp(booleano, "true") == 0);
                        setCorrecto = (strcmp(booleano, "true") == 0 || strcmp(booleano, "false") == 0);
                    }
                    if (strcmp(token, "raquetaDoble") == 0) {
                        checkearLadrillosAdministradorA(setget, &exito, setCorrecto, "Raqueta Doble",
                                                        valor, &ladrillo->raquetaDoble, &ladrillo->raquetaMitad);
                    } else if (strcmp(token, "raquetaMitad") == 0) {
                        checkearLadrillosAdministradorA(setget, &exito, setCorrecto, "Raqueta Mitad",
                                                        valor, &ladrillo->raquetaMitad, &ladrillo->raquetaDoble);
                    } else if (strcmp(token, "velocidadMas") == 0) {
                        checkearLadrillosAdministradorA(setget, &exito, setCorrecto, "Velocidad Mas",
                                                        valor, &ladrillo->velocidadMas, &ladrillo->velocidadMenos);
                    } else if (strcmp(token, "velocidadMenos") == 0) {
                        checkearLadrillosAdministradorA(setget, &exito, setCorrecto, "Velocidad Menos",
                                                        valor, &ladrillo->velocidadMenos, &ladrillo->velocidadMas);
                    } else if (strcmp(token, "vida") == 0) {
                        if (strcmp(setget, "set") == 0) {
                            if (setCorrecto) {
                                ladrillo->vida = valor;
                                exito = true;
                            }
                        } else {
                            printf(ladrillo->vida ? "Vida: true\n" : "Vida: false\n");
                            exito = true;
                        }
                    } else if (strcmp(token, "balon") == 0) {
                        if (strcmp(setget, "set") == 0) {
                            if (setCorrecto) {
                                ladrillo->balon = valor;
                                exito = true;
                            }
                        } else {
                            printf(ladrillo->balon ? "Balon: true\n" : "Balon: false\n");
                            exito = true;
                        }
                    }
                }
            }
        }
    }else if (setget!=NULL){
        if(strcmp(setget, "none") == 0) {
            exito = true;
        }else if(strcmp(setget, "exit") == 0){
            printf("\n\nTerminando ejecucion...\n\nHasta pronto vaquer@\n");
            terminate=true;
            exito = true;
        }
    }
    if(!exito){
        printf("Error en la entrada\n");
    }
}

void iniciar(){
    nuevasListas();
    iniciarCoordenadas();
    DWORD ThreadId;
    CreateThread(NULL, 0, iniciarServer,NULL, 0, &ThreadId);

    char texto[DEFAULT_BUFLEN];
    for(int i=0;i<DEFAULT_BUFLEN;i++){
        texto[i]='\0';
    }
    iniciarInteraccion();
    while(!terminate){
        actualizarJuego(texto);
        actualizacionDeAdministrador();
    }
    liberarListasIntermedio();
}