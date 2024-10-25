#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

#define nHilos 13
void *generosos(void* args){
    int idHilo = *(int *)args;
    for(int i = 0; i<1000; i++){
        printf("Hilo: %d, iteración: %d\n", idHilo, i);
        if(i%10 == 0){
           sched_yield(); 
        }
    }
}

void *noGenerosos(void* args){
    int idHilo = *(int *)args;
    for(int i = 0; i<1000; i++){
        printf("No soy un hijo generoso: %d\n", idHilo);
    }
}

int main(int argc, char *argv[]){
    pthread_t hilos[nHilos];

    for(int i = 0; i < nHilos-3; i++){
        printf("Crear hilo %d\n", i);
        pthread_create(&hilos[i], NULL, noGenerosos, &i);
    }
    for(int i = nHilos-3; i < nHilos; i++){
        printf("Crear hilo %d\n", i);
        pthread_create(&hilos[i], NULL, generosos, &i);
    }

    for(int i = 0; i < nHilos-1; i++){
        pthread_join(hilos[i], NULL);
    }

    exit(0);
}