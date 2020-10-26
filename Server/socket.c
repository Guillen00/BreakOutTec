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

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

SOCKET JugadorSocket;
SOCKET EspectadoresSockets[MAX_CLIENTS];
int jugadorActivo;
int espectadorActivo[MAX_CLIENTS];

extern int terminate;

int recibirMensaje(SOCKET ClientSocket,char* rec){
    int iResult = recv(ClientSocket, rec, DEFAULT_BUFLEN, 0);
    char* current= rec;
    while(iResult==DEFAULT_BUFLEN){
        current+=iResult;
        iResult = recv(ClientSocket, current, DEFAULT_BUFLEN, 0);
    }
    if(iResult<0){
        closesocket(ClientSocket);
        shutdown(ClientSocket, SD_SEND);
        return 1;
    }
    return 0;
}

int enviarMensaje(SOCKET ClientSocket,char* message){
    int iSendResult = send(ClientSocket, message, strlen(message)+1, 0);
    if (iSendResult == SOCKET_ERROR) {
        closesocket(ClientSocket);
        return 1;
    }
    return 0;
}

int isJugadorActivo(){
    return jugadorActivo;
}

void anularEspectadores(){
    for(int i =0;i<MAX_CLIENTS;i++){
        {
            closesocket(espectadorActivo[i]);
            espectadorActivo[i]=false;
        }
    }
}

int recibirDatos(char* datos){
    int resultado;
    if(jugadorActivo){
        resultado=recibirMensaje(JugadorSocket,datos);
        if(resultado==MESSAGE_ERROR){
            jugadorActivo=false;
            anularEspectadores();
        }
    }else{
        resultado=MESSAGE_ERROR;
    }
    return resultado;
}


void enviarDatos(char* datos){
    for(int i =0;i<MAX_CLIENTS;i++){
        if(espectadorActivo[i]){
            int resultado=enviarMensaje(EspectadoresSockets[i],datos);
            if(resultado==MESSAGE_ERROR){
                espectadorActivo[i]=false;
            }
        }
    }
}

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