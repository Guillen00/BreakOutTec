//
// Created by alfab on 10/22/2020.
//

#ifndef SERVER_INTERACCION_H
#define SERVER_INTERACCION_H

#define COMMAND_LEN 100

/**
 * Funcion para leer el siguiente comando del usuario
 * @param dest Char en el cual se escribe el comando
 */
void getComando(char* dest);

/**
 * Funcion para iniciar la linea de comandos
 */
void iniciarInteraccion();
#endif //SERVER_INTERACCION_H
