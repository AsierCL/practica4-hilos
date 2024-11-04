/*  
    Si el numero de hilos empleado en el programa es superior al número de cores de mi equipo,
    en esta caso 16 cores; el tiempo de ejecución aumenta en comparación con una ejecución en la
    que empleo extactamente 16 cores. Esto sucede ya que el sistema operativo distribuye el tiempo
    de CPU entre todos los hilos, lo que significa que los hilos se bloqueen y mientras que este
    está bloqueado deja que otros hilos, que estaban esperando a que se libere algun núcleo, 
    utilicen la CPU. Este proceso de intercambio entre hilos genera un sobrecarga que termina 
    ralentizando la ejecución del programa.
    
    El uso de un gran numero de hilos no contribuye a una mayor velocidad, sino que hace que cada
    hilo pase más tiempo esperando en cola a que un núcleo se libere; por lo tanto, tener más hilos
    que núcleos en este programa no mejora el rendimiento, de hecho, lo empeora. Aun así, sigue
    habiendo ejecución en paralelo.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOTAL_ITERACIONES 1000000000  // Número total de iteraciones a calcular
#define NUM_HILOS 16                // Número de hilos a crear
#define RANGO 10               // Rango que procesará cada hilo en cada iteración

double sumaParcialHilos[NUM_HILOS] = {0};

void *funcion(void *args) {
    int idHilo = *(int *)args;  // Obtener el ID único de cada hilo
    double sumaParcial = 0;
    double sumaTotalHilo = 0;
    double inicio, fin;

    // Asignación de bloques en rondas cíclicas
    for (double k = idHilo * RANGO + 1; k <= TOTAL_ITERACIONES; k += NUM_HILOS * RANGO) {
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


    // Calculamos la suma total secuencial en el hilo principal.
    for (double i = 1.0; i <= TOTAL_ITERACIONES; i+=1.0) {
        sumaSecuencial += 1.0/(i*i);
    }   
    printf("\nSuma secuencial: %.18f\n", sumaSecuencial);

    // Calculamos la diferencia entre la suma secuencial y suma paralela.
    diferenciaSumas = sumaSecuencial - sumaParalela;
    printf("La diferencia entre la suma secuencia y paralela es: %.18f\n", diferenciaSumas);

    // Calculamos la diferencia entre la suma paralela y el valor exacto 
    diferenciaValorExacto =  sumaParalela - (M_PI*M_PI)/6;
    printf("La diferencia entre la suma paralela y el valor exacto es: %.18f\n", diferenciaValorExacto);






    return 0;
}
