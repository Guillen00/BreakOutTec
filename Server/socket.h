//
// Created by alfab on 10/19/2020.
//

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#define DEFAULT_BUFLEN 2048
#define DEFAULT_PORT "27015"
#define MAX_CLIENTS 10
#define MESSAGE_ERROR 1
int recibirDatos(char* datos);
void enviarDatos(char* datos);
int isJugadorActivo();
int iniciarServer();

#endif //SERVER_SOCKET_H
