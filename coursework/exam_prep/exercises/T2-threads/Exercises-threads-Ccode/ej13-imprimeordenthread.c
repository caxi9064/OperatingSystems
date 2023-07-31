
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_THREADS 10

void *funcionThread(void *numero);

int main(){
    int j; 
    int k;

    pthread_t thid[MAX_THREADS]; /*array con los identificadores de los threads que se van a crear*/

    pthread_attr_t attr; /*variable con los atributos de los threads que se van a crear*/
    pthread_attr_init(&attr); /*se inicializan los atributos (a por defecto)*/

    /*bucle para crear los distintos threads*/
    for(j = 0; j < MAX_THREADS; j++)
    {
	pthread_create(&thid[j], &attr, (void *) funcionThread, &j);

	sleep(1); /*se duerme el proceso para que el thread recien creado le de tiempo a ejecutar*/
    }

    /*bucle para esperar por la finalizacion de los distintos threads*/
    for(k = 0; k < MAX_THREADS; k++)
    {
	pthread_join(thid[k], NULL);
    }

    return(0);
}

void *funcionThread(void *numero) {

    //sleep(1); /*si se duerme el thread, no le da tiempo a coger el valor del parametro*/

    int valor = *((int *)(numero));

    printf("Thread con numero %d \n", valor); /*imprime el numero que recibe por parametro*/

    pthread_exit(0); /*hace que termine el thread y se mande el estado de terminacion al padre*/
}

