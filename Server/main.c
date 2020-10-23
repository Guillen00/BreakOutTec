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

    return 0;
}
