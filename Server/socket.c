#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wspiapi.h>
#include "socket.h"
#include "estructuras.h"

// Link con Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

/**
 * Se definen las variables de los clientes
 */
SOCKET JugadorSocket;
SOCKET EspectadoresSockets[MAX_CLIENTS];
int jugadorActivo;
int espectadorActivo[MAX_CLIENTS];

extern int terminate;


/**
 * Funcion para recibir un mensaje de un cliente
 * @param ClientSocket Cliente del cual recibir
 * @param rec Char en el cual se devuelve el mensaje
 * @return Entero con el resultado de la operacion
 */
int recibirMensaje(SOCKET ClientSocket,char* rec){
    int iResult = recv(ClientSocket, rec, DEFAULT_BUFLEN, 0);
    char* current= rec;
    while(iResult==DEFAULT_BUFLEN){
        current+=iResult;
        iResult = recv(ClientSocket, current, DEFAULT_BUFLEN, 0);
    }
    if(iResult<0){
        closesocket(ClientSocket);
        shutdown(ClientSocket, SD_BOTH);
        return 1;
    }
    return 0;
}

/**
 * Funcion para enviar un mensaje a un cliente
 * @param ClientSocket Cliente al cual enviar el mensaje
 * @param message Mensaje a enviar
 * @return Un entero que indica el resultado de la operacion
 */
int enviarMensaje(SOCKET ClientSocket,char* message){
    int iSendResult = send(ClientSocket, message, strlen(message)+1, 0);
    if (iSendResult == SOCKET_ERROR) {
        closesocket(ClientSocket);
        shutdown(ClientSocket, SD_BOTH);
        return 1;
    }
    return 0;
}


/**
 * Funcion para comprobar si el cliente jugador se encuentra activo
 * @return Entero que indica si el jugador esta activo
 */
int isJugadorActivo(){
    return jugadorActivo;
}


/**
 * Funcion para leer los datos enviados por el cliente
 * @param datos Texto en donde se guardan los datos recibidos
 * @return Entero que indica si la funcion fue exitosa
 */
int recibirDatos(char* datos){
    int resultado;
    if(jugadorActivo){
        resultado=recibirMensaje(JugadorSocket,datos);
        if(resultado==MESSAGE_ERROR){
            jugadorActivo=false;
            //anularEspectadores();
        }
    }else{
        resultado=MESSAGE_ERROR;
    }
    return resultado;
}

/**
 *  Funcion para enviar datos a los clientes
 * @param datos Datos a enviar
 */
void enviarDatos(char* datos){
    for(int i =0;i<MAX_CLIENTS;i++){
        if(espectadorActivo[i]){
            int resultado=enviarMensaje(EspectadoresSockets[i],datos);
            if(resultado==MESSAGE_ERROR){
                if(JugadorSocket==EspectadoresSockets[i]){
                    //anularEspectadores();
                    jugadorActivo=false;
                }
                espectadorActivo[i] = false;
            }
        }
    }
}
/**
 * Funcion para asignar el cliente jugador
 * @param ClientSocket Socket del cliente
 * @param message String que se usara para enviar un mensaje
 * @return
 */
int asignarJugador(SOCKET ClientSocket, char* message){
    if(!jugadorActivo){
        JugadorSocket=ClientSocket;
        jugadorActivo=true;
        return 0;
    }else{
        strcpy(message,"Error: Ya hay un Jugador");
        enviarMensaje(ClientSocket, message);
        closesocket(ClientSocket);
        return 1;
    }
}

/**
 * Funcion para agregar un espectador
 * @param ClientSocket Socket del espectador
 * @param message Mensaje enviado por el cliente
 * @return Retorna un entero que indica si hubo exito
 */
int asignarEspectador(SOCKET ClientSocket, char* message){
    int asignado=false;
    for(int i=0;i<MAX_CLIENTS;i++){
        if(!espectadorActivo[i]){
            EspectadoresSockets[i]=ClientSocket;
            espectadorActivo[i]=true;
            asignado =true;
            break;
        }
    }
    if(!asignado){
        strcpy(message,"Error: Pila llena");
        enviarMensaje(ClientSocket, message);
        closesocket(ClientSocket);
        return 1;
    }else{
        return 0;
    }
}

/**
 * Funcion para conectar un cliente y asignar su tipo
 * @param Param Socket
 * @return Parametro para el thread
 */
DWORD WINAPI connectionHandler(LPVOID Param){
    char rec[DEFAULT_BUFLEN];
    char message[DEFAULT_BUFLEN];
    int ClientSocket=(int)Param;
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        return 1;
    }

    if(recibirMensaje(ClientSocket,rec)==MESSAGE_ERROR){
        return 1;
    }
    if(strcmp("Tipo: Espectador", rec)==0){
        return asignarEspectador(ClientSocket, message);
    }else if(strcmp("Tipo: Jugador", rec)==0){
        if(asignarJugador(ClientSocket, message)==0){
            if(asignarEspectador(ClientSocket, message)==1){
                jugadorActivo=false;
                return 1;
            }else{
                return 0;
            }
        }else{
            return 1;
        }
    }else{
        closesocket(ClientSocket);
        return 1;
    }
}


/**
 * Funcion para inicializar el servidor
 * @return Valor para el thread
 */
DWORD WINAPI iniciarServer()
{

    for(int i=0;i<MAX_CLIENTS;i++){
       espectadorActivo[i]=false;
    }
    jugadorActivo=false;

    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }


    // Accept a client socket
    while(!terminate) {
        DWORD ThreadId;
        ClientSocket = accept(ListenSocket, NULL, NULL);
        CreateThread(NULL, 0, connectionHandler, (LPVOID) ClientSocket, 0, &ThreadId);
    }
    return 0;
}