#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_ITERACIONES 100  // Número total de iteraciones a calcular
#define NUM_HILOS 4            // Número de hilos a crear
#define RANGO 10               // Rango que procesará cada hilo en cada iteración

double sumaTotal = 0;          // Variable global para acumular la suma total
pthread_mutex_t mutex;         // Mutex para proteger acceso a `sumaTotal`

void *funcion(void *args) {
    int idHilo = *(int *)args;  // Obtener el ID único de cada hilo
    double sumaParcial = 0;
    int inicio, fin;

    // Asignación de bloques en rondas cíclicas
    for (int k = idHilo * RANGO + 1; k <= TOTAL_ITERACIONES; k += NUM_HILOS * RANGO) {
        inicio = k;
        fin = inicio + RANGO - 1;

        // Ajustar el límite superior si sobrepasa el total de iteraciones
        if (fin > TOTAL_ITERACIONES) {
            fin = TOTAL_ITERACIONES;
        }

        // Calcular la suma parcial para el rango asignado
        sumaParcial = 0;
        for (int i = inicio; i <= fin; i++) {
            sumaParcial += i;
        }

        // Bloquear el acceso a `sumaTotal` para acumular el resultado
        pthread_mutex_lock(&mutex);
        sumaTotal += sumaParcial;
        pthread_mutex_unlock(&mutex);

        printf("Hilo %d, suma parcial de %d a %d = %f\n", idHilo, inicio, fin, sumaParcial);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[NUM_HILOS];
    int ids[NUM_HILOS];
    pthread_mutex_init(&mutex, NULL);

    // Crear los hilos
    for (int i = 0; i < NUM_HILOS; i++) {
        ids[i] = i;
        pthread_create(&hilos[i], NULL, funcion, (void *)&ids[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Suma total: %f\n", sumaTotal);

    // Destruir el mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
