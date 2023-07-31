
/*José Manuel Pérez Lobato
Ejercicio simple de utilización de la salida estandar y la de errores.
Ejecutarlo con   programa >salida 2>errores
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
   int i=3;
  char cad[10];
   int j=3;

  write (STDOUT_FILENO, "Escrito en salida estandar \n", 
    strlen ("Escrito en salida estandar \n")); 
  write (STDERR_FILENO, "Escrito en salida errores \n", 
    strlen ("Escrito en salida errores \n")); 
}
