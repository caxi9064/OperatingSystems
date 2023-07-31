/*Ejemplo de porque hay que poner \n al final de la escritura.
 * La cadena Hola tarda 4 seg en aparecer
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char**argv){
  printf ("\nHola\n");
  sleep (atoi(argv[1]));
  printf ("adios\n");
}
