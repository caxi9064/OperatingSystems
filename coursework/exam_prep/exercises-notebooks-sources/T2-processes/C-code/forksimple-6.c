/* Este programa no crea "sÛlo" 4 hijos.
 * ModifÌcalo para que cree sÛlo 4 hijos 
JosÈ Manuel PÈrez Lobato
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void fhijo(int i){
    printf ("Hijo %d, pid =%d, ppid%d\n",i, getpid(),getppid());
     /*Puedes probar a comentar/descomentar el exit para ver la diferencia*/
    exit (0); 
}

int main (){
int i,pid;

for (i=0; i<4; i++){
  pid=fork();
  if (pid==0){ //Hijo
    fhijo(i);
  }
  else
    printf ("El padre ha creado %d hijos \n",i);
} // fin for

} // fin main

