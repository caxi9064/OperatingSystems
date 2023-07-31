// fichero ej8-multiplicarthread.c
//THREADS
/* Realizar un programa que declare una función multiplicar y que le pase como parámetros 2 números en una estructura 
A continuación el programa principal debe preparar los parámetros del thread y lanzar 1 thread con func1, escribir su propiedad identidad y terminar. */
// compilar con  gcc -lpthread ej8-multiplicarthread.c
//Jesús Carretero

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Estructura que contiene los datos a pasar como parámetros 
// Un único parámetro se puede pasar directamente con el 
// operador &

typedef struct 
{ 
   int dato1,dato2;
}datos; 

pthread_t thread1, thmain; /* Declaración de los threads */
pthread_attr_t attr; /*atributos de los threads*/ 

/* Definición de las función func1 */
void *multiplicar (void *arg) 
{ 
  int a,b; 
  datos *p= (datos *) (arg); 
  pthread_t tid = pthread_self(); /*identificador de thread*/ 

  a=(p->dato1); 
  b=(p->dato2); 
  printf("Soy el thread 1 y voy a multiplicar \n"); 
  printf("La multiplicacion es %d\n",a*b); 
  printf("Soy el thread 1 y he terminado de multiplicar \n"); 
  pthread_exit (NULL); 
}


/*Función main*/ 
int main(int argc, char* argv[])
{ 
  datos param; 
  param.dato1=atoi(argv[1]); 
  param.dato2=atoi(argv[2]); 
  thmain = pthread_self(); 
  
  pthread_attr_init (&attr); 
  printf("Soy la funcion main y voy a lanzar el thread \n"); 
  pthread_create (&thread1, &attr, multiplicar, &param); 
  printf("Soy main: he lanzado el thread y termino\n"); 
  pthread_exit (NULL); 
} 
