/* Este programa sirve como ejemplo del uso de threads con parámetros
  Hay que compilarlo con gcc -lpthread argvint-1.c
José Manuel Pérez Lobato 
*/

#include <stdio.h>
#include <pthread.h>


void *f( void *arg){
int *v;

//Forma complicada de acceder a los argumentos
int i,j,k;

printf ("Inicio ejecución del thread\n");
i=*((int *)(arg));
j=*((int *)(arg)+1);
k=*((int *)(arg)+2);
printf ("TH:arg con i,j,k:%d, %d, %d:\n", i,j,k);	

//Forma simple de acceder a los argumentos
v=(int *)arg;
printf ("TH:arg con v:%d, %d, %d:\n", v[0],v[1],v[2]);	
printf ("Fin ejecucion el thread\n");
}

main (){
pthread_attr_t attr;
int argu[4];
pthread_t thid;

argu[0]=99;
argu[1]=11;
argu[2]=22;
printf ("En el main:argu:%d, %d, %d:\n", argu[0],argu[1], argu[2]);	

//f(argu);
        pthread_attr_init (&attr);
 //Puedes probar a crearlo DETACHED y esperar con un sleep aunque es peor opción
 //       pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
	pthread_create (&thid, &attr, f, (void *)argu);
	pthread_join(thid,NULL);
//sleep(2);
}

