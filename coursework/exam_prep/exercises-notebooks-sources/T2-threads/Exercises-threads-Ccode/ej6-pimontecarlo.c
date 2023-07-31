#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>



#define RADIO 5000
#define PUNTOS 1000000

//Variable global compartida por todos los threads, incluido el main
float valoresPIthreads[10]; 

void *calcula_pi (void *kk);

void main() {
	pthread_attr_t attr;
	pthread_t thread[10];
	int i;
	float *valorpi=0, suma=0, media=0;
	
	pthread_attr_init(&attr);
	for (i=0;i<10;i++) {
		pthread_create(&thread[i],&attr,calcula_pi,&i);
//Ponemos un sleep para que le de tiempo al thread a coger el valor de i.
//Hay mejores mÈtodos que veremos m·s adelante. 
//Puedes probar a quitar el sleep para ver que pasa
		sleep(1); 
printf ("Creado thread %d\n",i);
	}
	for (i=0;i<10;i++) {
		pthread_join(thread[i],NULL);
	}
	for (i=0;i<10;i++) {
		printf("Valor del thread %d: %f\n",i,valoresPIthreads[i]);
		suma=suma+valoresPIthreads[i];
	}
	media=suma/10.0;
	printf("El valor medio de Pi obtenido es: %f\n",media);
}

void *calcula_pi (void *idthread)
{
	int j, y=0, x=0, cont=0,numthread;
	float pi=0, h=0;
	numthread=*((int *)idthread);
printf ("Inicio th %d\n", numthread);
	srandom(pthread_self());
	for (j=0;j<PUNTOS;j++) {
		y=(random()%((2*RADIO)+1)-RADIO);
		x=(random()%((2*RADIO)+1)-RADIO);
		h=sqrt((x*x)+(y*y));
		if ( h<=RADIO ) cont++;
	}
	valoresPIthreads[numthread]=(cont*4)/(float)PUNTOS;
	pthread_exit(&pi);
}

