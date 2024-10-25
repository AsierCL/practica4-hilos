#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

//
#define nHilos 16
#define nIteraciones 20
double sumaTotal = 0;
void *funcion(void* args){

    int idHilo = *(int *) args;
    double sumaParcial = 0;
    for(int i = 0; i < nIteraciones; i++){
        if((i-1) % nIteraciones == idHilo){
            sumaParcial +=i;
        } 
    }
    sumaTotal += sumaParcial;
    printf("Hilo %d, suma parcial = %f\n", idHilo, sumaParcial);
    
    pthread_exit(NULL);
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
