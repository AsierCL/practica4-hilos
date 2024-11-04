#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

#define nHilos 16
float datos[nHilos];

void *funcion(void* args){
    int idHilo = *(int *)args;
    printf("Id de hilo:%d\n",idHilo);
    datos[idHilo]=idHilo*0.1f;
}


int main(int argc, char const *argv[]){
    pthread_t hilos[nHilos];

    for(int i=0; i<nHilos-1; i++){
        pthread_create(&hilos[i], NULL, funcion, &i);
    }
    
    for(int i=0; i<nHilos-1; i++){
        pthread_join(hilos[i], NULL);
    }

    printf("Total: %f",datos[3]);

    return 0;
}
