#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *printear(void *arg) {
    int valor = *(int *)arg;  // Convertimos void* a int* y luego accedemos al valor
    printf("Valor recibido en el hilo: %d\n", valor);
    return NULL;
}

void *modificar(void *arg) {
    int *valor;
    valor = (int *)arg;
    *valor=4;
    printf("Valor modificado en el hilo: %d\n", *valor);
    return NULL;
}

int main() {
    pthread_t hilo,hilo2;
    int num = 5;  // Variable que queremos pasar al hilo

    // Pasamos la dirección de num
    pthread_create(&hilo, NULL, printear, &num);
    pthread_join(hilo, NULL);
    pthread_create(&hilo2, NULL, printear, &num);
    pthread_join(hilo2, NULL);

    pthread_create(&hilo, NULL, modificar, &num);
    pthread_join(hilo, NULL);
    pthread_create(&hilo, NULL, printear, &num);
    pthread_join(hilo, NULL);
    pthread_create(&hilo2, NULL, printear, &num);
    pthread_join(hilo2, NULL);



    printf("Hilo terminado\n");
    return 0;
}