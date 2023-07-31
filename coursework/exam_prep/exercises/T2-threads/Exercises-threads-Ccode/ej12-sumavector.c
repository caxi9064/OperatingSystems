// fichero ej12-sumavector.c
//THREADS
// Realizar un programa que cree 1 thread que suma los valores que se le pasan como parámetro en un array de 10 enteros y cuando termina devuelve el valor calculado.
// compilar con  gcc -lpthread ej12-sumavector.c
//José Manuel Pérez Lobato
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void *suma(void *rango);


int main(){
pthread_attr_t attr;
pthread_t thread;
int rango[]={1,2,3,4,5,6,7,8,9,10};
int *resultado;
    
    pthread_attr_init(&attr);
   // Creo el thread
    pthread_create(&thread,&attr,suma,&rango);
  // Espero la finalización del thread
    pthread_join(thread,(void **)&resultado);
    printf("\nSuma  en Prog. Principal: %d\n",*resultado);
    return(0);
}

//Esta función la ejecuta el thread y realiza la suma del array recibido en rango
void *suma(void *rango) {
   int i=0, *valores; 
   int *suma; //variable de tipo puntero porque será devuelta al main y si no lo fuera se eliminaría el valor calculado cuando finalizara el thread 

   valores= (int *)rango;
   suma=(int *)malloc (sizeof (int));
   *suma=0;
   for(i=0;i<10;i++) {   
     *suma=*suma+valores[i];
   }
   printf("\tThread Suma : %d\n",*suma);
   pthread_exit(suma);
} 
