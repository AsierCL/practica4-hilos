#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

#define nHilos 16

void *funcion(void* args){
    
}


int main(int argc, char const *argv[]){
    pthread_t hilos[nHilos];

    for(int i=0; i<nHilos-1; i++){
        pthread_create(&hilos[i], NULL, funcion, &i);
    }
    
    for(int i=0; i<nHilos-1; i++){
        pthread_join(hilos[i], NULL);
    }

    return 0;
}
