#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define nHilos 10 // Número de hilos, cada uno cubrirá un rango fijo de 10
#define nIteraciones 100 // Rango total de iteraciones
#define rango 10 // Tamaño fijo del tramo para cada hilo

double sumaTotal = 0;
pthread_mutex_t mutex; // Mutex para proteger la suma total

void *funcion(void *args) {
    int idHilo = *(int *)args;  // Obtener el ID único de cada hilo
    double sumaParcial = 0;

    // Rango específico para cada hilo
    int inicio = idHilo * rango + 1;
    int fin = (idHilo + 1) * rango;

    for (int i = inicio; i <= fin; i++) {
        sumaParcial += i;
    }

    // Bloquear la sección crítica para proteger el acceso a `sumaTotal`
    pthread_mutex_lock(&mutex);
    sumaTotal += sumaParcial;
    pthread_mutex_unlock(&mutex);

    printf("Hilo %d, suma parcial de %d a %d = %f\n", idHilo, inicio, fin, sumaParcial);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    pthread_t hilos[nHilos];
    int ids[nHilos];
    pthread_mutex_init(&mutex, NULL); // Inicializar el mutex

    // Crear hilos
    for (int i = 0; i < nHilos; i++) {
        ids[i] = i; // Asignar un identificador único para cada hilo
        pthread_create(&hilos[i], NULL, funcion, &ids[i]);
    }

    // Esperar a que terminen todos los hilos
    for (int i = 0; i < nHilos; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Suma total = %f\n", sumaTotal);

    pthread_mutex_destroy(&mutex); // Destruir el mutex
    return 0;
}
