#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <time.h>
#include <pthread.h>
#include "socket.h"
#include "juego.h"
int main() {
    srand (time(NULL));
    srand (getpid());

    iniciar();


    pthread_t thread_id;
    pthread_create(&thread_id, NULL, (void *(*)(void *)) iniciarServer(), NULL );

    printf("w");
    return 0;
}
