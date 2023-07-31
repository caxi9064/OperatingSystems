/* José Manuel Pérez Lobato 
   Ejemplo de utilización del dup y del dup2 
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main () {

   int d,daux;

   /* Cierro la salida de errores */
   close (2);  
   /* Escrito en pantalla */
   printf ("UNO\n");  
   /* Abro un fichero en el descriptor asociado a la salida de errores ya que está libre porque lo acabo de cerrar*/
   d=open ("f.dat", O_CREAT|O_WRONLY,0777); 
   if (d<0) exit (1); /* Si hay error finalizo el programa*/
   /* copio la salida estandar al primer descritor libre ( en el descriptor 3 está "la pantalla") */
   daux=dup(1); 
   /* Asocio la salida estandar al fichero f.dat */ 
   dup2 (d,1);  
   /* Se escribe en el fichero f.dat*/
   printf ("DOS\n");  
   /* Asocio la salida estandar a lo que hay en daux (la pantalla)*/
   dup2(daux,1); 
   /* escrito en pantalla*/
   printf ("TRES\n"); 
}

