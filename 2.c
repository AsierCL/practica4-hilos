#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define nHilos 3
void *espera(void* args){
    while(1){
        sleep(1);
    }
}

void *procesoHijo(void* args){
    pid_t hijo = fork();

    if(hijo == 0){
        printf("Empieza proceso hijo.\n");
        sleep(20);
        printf("Este es el proceso hijo.\n");
    }else{
        printf("Empieza proceso padre.\n");
        sleep(20);
        printf("Este es el proceso padre.\n"); 
    }
    exit(0);
}
int main(int argc, char *argv[]){
    pthread_t hilos[nHilos];

    for(int i = 0; i < nHilos-1; i++){
        printf("Crear hilo %d\n", i);
        pthread_create(&hilos[i], NULL, espera, NULL);
    }
    pthread_create(&hilos[2], NULL, procesoHijo, NULL);
    pthread_join(hilos[2], NULL);

    exit(0);
}