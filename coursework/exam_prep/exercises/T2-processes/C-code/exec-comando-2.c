/* Este programa ejecuta en un proceso hijo el programa pasado como par·metro 
 * (que no puede tener argumentos).
 * Compilar con 
 *  gcc -o execcomando execcomando.c 
 * Probarlo ejecut·ndolo con 
 *   execcomando ls
 * o con 
 *   execcomando date
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define STDOUT 1

int main(int argc, char *argv[])
{
 int i,pid;

 if (argc < 2){
   printf("Usage: exec-comando <comando>\n");
   exit(-1);
 }
  
 pid=fork();
 if(pid==0){ //crear hijo
        printf ("Hijo creado, va a ejecutar el comando\n");
        // Redirección de salida 
        close(STDOUT);
        open("salida-com.txt",O_RDWR|O_CREAT,0660);
        // Ejecución comando
        execvp (argv[1], &argv[1]); 
	printf ("ERROR, aqui solo se llega si ha fallado el exec\n");
  }   
  wait (NULL);
  printf ("FIN  del padre\n");
 } //cierre del main

