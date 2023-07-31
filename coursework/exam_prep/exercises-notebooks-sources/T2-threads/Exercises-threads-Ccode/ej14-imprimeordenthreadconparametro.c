#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_THREADS 10

int arrayEnteros[MAX_THREADS];

void *funcionThread(void *numero);

int main() {
    int j, k; 
    int sumaAcumulada = 0;

    pthread_t thid[MAX_THREADS]; //array con los identificadores de los threads que se van a crear

    pthread_attr_t attr; //variable con los atributos de los threads que se van a crear
    pthread_attr_init(&attr); //se inicializan los atributos (a por defecto)

    //bucle para crear los distintos threads
    for(j = 0; j < MAX_THREADS; j++)
    {
	pthread_create(&thid[j], &attr, (void *)funcionThread, &j);

	sleep(1); //se duerme el proceso para que el thread recien creado le de tiempo a ejecutar
    }

    //bucle para esperar por la finalizacion de los distintos threads
    for(k = 0; k < MAX_THREADS; k++)
    {
 	pthread_join(thid[k], NULL);

	sumaAcumulada += arrayEnteros[k];
    }

    printf("La suma acumulada es: %d\n", sumaAcumulada);

    return(0);
}

void *funcionThread(void *numero) {

    int posicion = *((int *)(numero));

    int numeroAleatorio = (int)(random() % 10);
	
    printf("El thread de la posicion %d genero el numero: %d\n", posicion, numeroAleatorio);

    arrayEnteros[posicion] = numeroAleatorio;

    pthread_exit(0); //hace que termine el thread y se mande el estado de terminacion al padre
}

