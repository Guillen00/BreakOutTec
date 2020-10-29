#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <time.h>
#include "socket.h"
#include "juego.h"
/**
 * Metodo main del programa
 * @return 0
 */
int main() {
    srand (time(NULL));
    srand (getpid());
    iniciar();
    return 0;
}
