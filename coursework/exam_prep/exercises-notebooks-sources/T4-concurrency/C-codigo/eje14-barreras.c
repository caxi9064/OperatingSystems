#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMTHREADS 6
#define THBARRERA 3  //Primero pasan 3 y luego otros 3
pthread_barrier_t barrera;
pthread_t th[NUMTHREADS];

void * funcion(void * data){
int espera=random()%5;
   printf ("Espera %d thread %d\n", espera, pthread_self());	
   sleep(espera);
   pthread_barrier_wait(&barrera);
   printf ("Paso la barrera thread %d\n", pthread_self());	
   pthread_exit(NULL);
}

int main (int argc, char ** argv){
int i;
  pthread_barrier_init(&barrera, NULL, THBARRERA );
  for (i=0; i<NUMTHREADS; i++)
    pthread_create(&th[i], NULL, funcion, NULL);
  printf ("THS creados\n");
  for (i=0; i<NUMTHREADS; i++) {
    pthread_join(th[i], NULL);  //Espera por un thread concreto. Si el orden de finalización no es el de creación (ej. termina el 1 y luego el 0) espera por el 0 hasta que termine y luego espera por el 1)
    printf ("Fin th:%d\n", th[i]);
  }
  printf ("FIN\n");
}

