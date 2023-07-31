#include <stdio.h>
#include <unistd.h>
/*Ejemplo de uso del fork 
JosÈ Manuel PÈrez Lobato
*/

int main () {
int x=0,pid;
  printf ("Hola \n"); /*Escrito 1 sÛla vez en pantalla*/
  pid=fork (); /*Se crea el hijo */
  if (pid == 0){ 
    printf ("Soy el hijo\n"); /* Escrito por el hijo en pantalla*/
    printf ("Adios hijo; x=%d, pid=%d ppid=%d\n",x,getpid(), getppid()); 
  }
  else { 
    sleep(1);
    printf ("Soy el padre\n"); /* Escrito por el padre en pantalla*/
    printf ("Adios padre; x=%d, pid=%d ppid=%d\n",x,getpid(), getppid()); 
  }
}
