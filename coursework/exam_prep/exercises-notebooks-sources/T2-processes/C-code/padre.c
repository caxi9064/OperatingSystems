/* Este programa crea 3 hijos y cada uno de ellos ejecuta el fichero hijo con el
 * par·metro num que varÌa entre 1 y 3
 * para la ejecuciÛn del cÛdigo de los hijos se utiliza execlp
 //JosÈ Manuel PÈrez Lobato
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUMHIJOS 3
int main()
{
 int i,pid;
 char num[10];

  for(i=1;i<=NUMHIJOS;i++) {
      sprintf(num,"%d",i);
      pid=fork();
      if(pid==0) // hijo
        execlp("./hijo","hijo",num,NULL);
  } 
  for(i=1;i<=NUMHIJOS;i++) 
    wait (NULL);
    
 } //cierre del main
