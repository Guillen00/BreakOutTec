//
// Created by alfab on 10/20/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include "estructuras.h"
#include "parser.h"
#include "constants.h"
#include "socket.h"
#include "interaccion.h"
#include "windows.h"


/**
 * Se inicializan y definen constantes del juego
 */

/**
 * Se crea la estructura de juego inicial
 */
struct juego juego={NULL,.url=NULL,.imagenumber=0,.puntaje=0,0,0,NULL,puntajeVerdeInicial,puntajeAmarilloInicial,
                    puntajeNaranjIniciala,puntajeRojoInicial,probRaqMitadinicial,
                    probRaqDobleinicial,probVelMasinicial,probVelMenosinicial,
                    probVidaInicial,probBalonInicial};
/**
 * Char array para almacenar la imagen
 */
char url[500000];
/**
 * Constante que indica si ya termina la ejecucion
 */
int terminate=0;


/**
 * Funcion para eliminar de la memoria todas las listas del juego
 */
void liberarListasIntermedio(){
    for(int i=0;i<numFilas;i++) {
        liberarLista(&juego.listas[i]);
    }
}


/**
 * Funcion para generar nuevas listas de juego (nuevas filas con nuevos ladrillos)
 */
void nuevasListas(){
    for(int i=0;i<8;i++){
        juego.listas[i]=*crearFila(i/2, &juego);
    }
}

/**
 * Algoritmo para incrementar la dificultad del juego
 */
void algoritmoDeCambioExponencial(){
    juego.probRaqMitad*=2;
    juego.probRaqDoble/=2;
    juego.probVelMas*=2;
    juego.probVelMenos/=2;
    juego.probVida/=2;
    juego.probBalon*=2;
}

/**
 * Funcion que se encarga de subir de nivel cuando es necesario
 */
void checkearSubirNivel(){
    if(juego.subirNivel) {
        algoritmoDeCambioExponencial();
        liberarListasIntermedio();
        nuevasListas();
        juego.subirNivel=0;
    }
}

/**
 * Funcion que se encarga de subir el puntaje cuando es necesario
 * @param ladrillo Ultimo ladrillo destruido
 */
void subirPuntaje(struct ladrillo* ladrillo){
    if(ladrillo!=NULL) {
        int color = ladrillo->color;
        if (color == VERDE) {
            juego.puntaje += juego.puntajeVerde;
        } else if (color == AMARILLO) {
            juego.puntaje += juego.puntajeAmarillo;
        } else if (color == NARANJA) {
            juego.puntaje += juego.puntajeNaranja;
        } else if (color == ROJO) {
            juego.puntaje += juego.puntajeRojo;
        }
    }
}

/**
 * Funcion que se encarga del ciclo del juego
 * @param texto Char array para guardar datos
 */
void actualizarJuego(char* texto){
    if(isJugadorActivo()) {
        juegoToChar(texto, &juego);
        enviarDatos(texto);
        juego.ladrillo=NULL;

        ///Se reciben los datos
        for(int i=0;i<500000;i++){
            texto[i]='\0';
        }
        if(isJugadorActivo()) {
            if (recibirDatos(texto) != MESSAGE_ERROR) {
                if (*texto != '\0') {
                    charToJuego(texto, &juego);
                    checkearSubirNivel();
                    subirPuntaje(juego.ladrillo);
                }
            }
        }
    }else{
        juego.puntaje=0;
    }
}

/**
 * Funcion para realizar cambios en un ladrillo
 * @param setget Char que indica si la operacion es de get o de set
 * @param exito Char para indicar si se logró implementar lo pedido
 * @param setCorrecto Bool que indica si el mensaje original es correcto
 * @param texto Char que indica el mensaje a mostrar al usuario
 * @param valorNuevo Int que da el nuevo valor para la propiedad dle ladrillo
 * @param valor Puntero que indica la propiedad anterior
 * @param valorOpuesto Puntero que indica la propiedad opuesta del ladrillo
 */
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

/**
 * Funcion para realizar cambios en los puntajes
 * @param setget Char que indica si la operacion es de get o de set
 * @param number Nuevo valor de puntaje
 * @param exito Char para indicar si se logró implementar lo pedido
 * @param texto Char que indica el mensaje a mostrar al usuario
 * @param valor Puntero que da el valor anterior del puntaje
 */
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


/**
 * Funcion para realizar actualizaciones indicadas por el administrador
 */
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
                bool numericosCorrectos = number1 > 0 && number2 > 0 && number1 < 9 && number2 < (numCol + 1);

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


/**
 * Funcion para iniciar la logica del server/juego
 */
void iniciar(){
    nuevasListas();
    DWORD ThreadId;
    CreateThread(NULL, 0, iniciarServer,NULL, 0, &ThreadId);

    char texto[500000];
    juego.url=url;

    for(int i=0;i<500000;i++){
        url[i]='\0';
    }
    _getcwd(url, sizeof(url));
    iniciarInteraccion();
    while(!terminate){
        actualizarJuego(texto);
        actualizacionDeAdministrador();
    }
    liberarListasIntermedio();
}