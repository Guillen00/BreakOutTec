//
// Created by alfab on 10/19/2020.
//
#include "windows.h"

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#define MESSAGE_ERROR 1

/**
 * Funcion para leer los datos enviados por el cliente
 * @param datos Texto en donde se guardan los datos recibidos
 * @return Entero que indica si la funcion fue exitosa
 */
int recibirDatos(char* datos);
/**
 *  Funcion para enviar datos a los clientes
 * @param datos Datos a enviar
 */
void enviarDatos(char* datos);

/**
 * Funcion para comprobar si el cliente jugador se encuentra activo
 * @return Entero que indica si el jugador esta activo
 */
int isJugadorActivo();
/**
 * Funcion para inicializar el servidor
 * @return Valor para el thread
 */
DWORD WINAPI iniciarServer();

#endif //SERVER_SOCKET_H
