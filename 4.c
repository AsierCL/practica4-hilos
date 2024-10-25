#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

#define nHilos 13
void *generosos(void* args){
    int idHilo = *(int *)args;
    for(int i = 0; i<10000000; i++){
        double x=234182364918273467/12234*i;
        double y=x/1550*i;
        double z = x/y;
        if(i%10 == 0){
            sched_yield(); 
        }
    }
    printf("Hilo generoso terminado, num de hilo=%d\n",idHilo);
}

void *noGenerosos(void* args){
    int idHilo = *(int *)args;
    for(int i = 0; i<10000000; i++){
        double x=234182364918273467/12234*i;
        double y=x/1550*i;
        double z = x/y;
        //printf("No soy un hijo generoso: %d\n", idHilo);
    }
    printf("Hilo no generoso terminado, num de hilo=%d\n",idHilo);
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