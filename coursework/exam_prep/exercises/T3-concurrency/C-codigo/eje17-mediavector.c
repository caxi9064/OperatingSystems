// fichero mediavector.c
//THREADS
// Se tiene un array de 100 elementos en el que se quiere realizar varias iteracciones en cada una de las cuales se debe colocar en cada casilla la media de la suma del contenido de esa casilla y sus dos adyacente. Es decir que para cualquier casilla del array entre 1 y 98 el nuevo valor de la casilla sera v[i]= (v[i-1]+v[i]+v[i+1])/3; para la casilla 0 se aplicará el mismo procedimiento pero supeniendo que su adyacente izquierda es la casilla 99 y para la casilla 99 se supondrá que su adyacente derecha es la casilla 0.
// El procedimiento se aplicará durante 10 iteracciones y para optimizar se desea que la mitad del array la procese un thread y la otra mitad otro thread.
// Las operacicones de calculo de los nuevos valores se realizarán en un array auxiliar y sólo cuando los dos threads hayan terminado su iteración volcarán los valores del array real al auziliar para continuar con la siguiente iteracción.
// Por tanto el procedimiento que sequira cada thread es¨:
// 1.- Copiar los nuevos valores en el array auxiliar
// 2.- Cuando haya terminado de copiarlos deberá experar a que termine el otro thread antes de volcar los datos del array auxiliar en el array real.  De esta forma no se modifican los datos de una iteracción antes de que el otro utilice la casilla que tienen en comun
// 3.- Una vez copiados los datos en el array real deberá esperar a que el otro thread termine tambien de copiar los datos auxilares sobre el array real antes de proceder a la siguiente iteracción del paso 1. Al igual que en el paso 2, hay que esperar para que las casillas comunes estén actualizadas.
// compilar con  gcc -lpthread mediavector.c
// José Manuel Pérez Lobato

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TAM 10
#define NUMITER 20
pthread_attr_t attr;
pthread_t idth[2];
pthread_mutex_t mtx1,mtx2;
pthread_cond_t varcond1,varcond2;
int contfin1=0, contfin2=0;
float v[TAM];

void rellenarArray(){
  int i;
    for (i=0; i<TAM;i++)
      v[i]=i;
}
void mostrarArray(){
  int i;
    for (i=0; i<TAM;i++)
      printf (":%.2f", v[i]);
    printf ("\n"); 
}
void *hilo0(void *num) {
   int i,j;
   float vaux[TAM/2];
   int yoinicializo1=0, yoinicializo2=0;

printf ("Hilo 0\n");
for (j=0; j<NUMITER; j++) {
   vaux [0]= (v[TAM-1]+v[0]+v[1])/3;
   for (i=1; i<TAM/2 ; i++)
     vaux [i]= (v[i-1]+v[i]+v[i+1])/3;
   pthread_mutex_lock (&mtx1);
     contfin1++;
     //El que  va a esperar en el wait será el encargado de inicializar la variable contfin1 para la siguiente iteracción
     if (contfin1==1) yoinicializo1=1;
   //Esperar que termine el otro si no ha terminado 
     while (contfin1!=2)
       pthread_cond_wait(&varcond1, &mtx1);
     for (i=0; i<TAM/2 ; i++)
       v[i]=vaux[i];
     pthread_cond_signal(&varcond1);
     if (yoinicializo1){
       contfin1=0;
       yoinicializo1=0;
     }
   pthread_mutex_unlock (&mtx1);

   pthread_mutex_lock (&mtx2);
     contfin2++;
     if (contfin2==1) yoinicializo2=1;
   //Esperar  a que el otro copie los datos 
     while (contfin2!=2)
          pthread_cond_wait(&varcond2, &mtx2);
     pthread_cond_signal(&varcond2);
     if (yoinicializo2){
       contfin2=0;
       yoinicializo2=0;
       mostrarArray();
     }
   pthread_mutex_unlock (&mtx2);
} 
pthread_exit(0);
} 
void *hilo1(void *num) {
   int i,j;
   float vaux[TAM/2];
   int yoinicializo1=0, yoinicializo2=0;

printf ("Hilo 1\n");
for (j=0; j<NUMITER; j++) {
   for (i=TAM/2; i<TAM-1 ; i++)
     vaux [i-TAM/2]= (v[i-1]+v[i]+v[i+1])/3;
   vaux [TAM/2-1]= (v[TAM-2]+v[TAM-1]+v[0])/3;
   pthread_mutex_lock (&mtx1);
     contfin1++;
     //El que  va a esperar en el wait será el encargado de inicializar la variable contfin1 para la siguiente itereacción
     if (contfin1==1) yoinicializo1=1;
   //Esperar que termine el otro si no ha terminado 
     while (contfin1!=2)
       pthread_cond_wait(&varcond1, &mtx1);
       for (i=TAM/2; i<TAM ; i++)
         v[i]=vaux[i-TAM/2];
     pthread_cond_signal(&varcond1);
     if (yoinicializo1){
       contfin1=0;
       yoinicializo1=0;
     }
   pthread_mutex_unlock (&mtx1);

   pthread_mutex_lock (&mtx2);
     contfin2++;
     if (contfin2==1) yoinicializo2=1;
   //Esperar  a que el otro copie los datos 
     while (contfin2!=2)
          pthread_cond_wait(&varcond2, &mtx2);
     pthread_cond_signal(&varcond2);
     if (yoinicializo2){
       contfin2=0;
       yoinicializo2=0;
       mostrarArray();
     }
   pthread_mutex_unlock (&mtx2);
} 
pthread_exit(0);
} 

int main(){
   int i;
 
    rellenarArray(); 
    pthread_mutex_init (&mtx1, NULL); 
    pthread_mutex_init (&mtx2, NULL); 
    pthread_attr_init(&attr);
    pthread_create(&idth[0],&attr,hilo0,NULL);
    pthread_create(&idth[1],&attr,hilo1,NULL);
  // Espero la finalización de los threads
    for (i=0; i<2; i++) 
      pthread_join(idth[i],NULL);
    return(0);
}

