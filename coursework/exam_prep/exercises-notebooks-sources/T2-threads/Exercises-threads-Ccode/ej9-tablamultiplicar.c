// fichero ej9-tablamultiplicar.c
//THREADS
/* Realizar un programa que declare una función multiplicar y
 que le pase como parámetros 2 números en una estructura 
A continuación el programa principal debe preparar los parámetros del thread y lanzar 10 thread con multiplicar. El multiplicando será 6 y  a cada thread se le pasa el i como multiplicador  escribir su propiedad identidad y terminar. */
// compilar con  gcc -lpthread ej-tablamultiplicar.c
//Jesús Carretero

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

/* Definición de las función multiplicar */
void *multiplicar (void *arg) 
{ 
  int a,b; 
  datos *p= (datos *) (arg); 
  pthread_t tid = pthread_self(); /*identificador de thread*/ 

  a=(p->dato1); 
  b=(p->dato2); 
  printf("%d por %d es %d\n",a, b, a*b); 
  pthread_exit (NULL); 
}


/*Función main*/ 
int main(int argc, char* argv[])
{ 
  datos param;
  int i;
  
  param.dato1=atoi(argv[1]); 
  thmain = pthread_self(); 
  
  pthread_attr_init (&attr); 
  printf("Soy la funcion main. Tabla de multiplicar del %d \n", param.dato1); 
  for (i=0; i<= 10; i++) {
      param.dato2=i; 
      pthread_create (&thread1, &attr, multiplicar, &param); 
      sleep(1);
  }
  printf("Soy main pid= %d: he lanzado los thread y termino\n", getpid()); 
  pthread_exit (NULL); 
} 
