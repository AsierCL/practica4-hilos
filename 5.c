#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOTAL_ITERACIONES 100000000000  // Número total de iteraciones a calcular
#define NUM_HILOS 16           // Número de hilos a crear
#define RANGO 10               // Rango que procesará cada hilo en cada iteración

double sumaParcialHilos[NUM_HILOS] = {0};

void *funcion(void *args) {
    int idHilo = *(int *)args;  // Obtener el ID único de cada hilo
    double sumaParcial = 0;
    double sumaTotalHilo = 0;
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
        for (double i = inicio; i <= fin; i+=1.0) {
            sumaParcial += 1.0/(i*i);
        }

       // printf("Hilo %d, suma parcial de %d a %d = %f\n", idHilo, inicio, fin, sumaParcial);
        sumaTotalHilo += sumaParcial;
    }

    sumaParcialHilos[idHilo] = sumaTotalHilo;

    pthread_exit(NULL);
}

int main() {
    double sumaParalela = 0;
    double sumaSecuencial = 0;
    double diferenciaSumas = 0;
    double diferenciaValorExacto = 0;
    pthread_t hilos[NUM_HILOS];
    int ids[NUM_HILOS];

    // Crear los hilos
    for (int i = 0; i < NUM_HILOS; i++) {
        ids[i] = i;
        pthread_create(&hilos[i], NULL, funcion, (void *)&ids[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    /* Esto aparece en comentarios ya que así verificamos que el número de iteraciones es correcto
    double sumaEsperada = (TOTAL_ITERACIONES * (TOTAL_ITERACIONES + 1))/2.0;
    printf("Suma esperada: %f\n", sumaEsperada);
    */
    
    for(int i=0;i<NUM_HILOS;i++){
        sumaParalela += sumaParcialHilos[i];
        printf("Suma paralela (hilo %d): %f\n",i, sumaParalela);
    }
    printf("\n\nSuma paralela: %.18f\n", sumaParalela);


    //sumaSecuencial = 0;
    for (double i = 1.0; i <= TOTAL_ITERACIONES; i+=1.0) {
        sumaSecuencial += 1.0/(i*i);
    }   
    printf("\nSuma secuencial: %.18f\n", sumaSecuencial);

    diferenciaSumas = sumaSecuencial - sumaParalela;
    printf("La diferencia entre la suma secuencia y paralela es: %.18f\n", diferenciaSumas);

    diferenciaValorExacto =  sumaParalela - (M_PI*M_PI)/6;
    printf("La diferencia entre la suma paralela y el valor exacto es: %.18f\n", diferenciaValorExacto);






    return 0;
}
