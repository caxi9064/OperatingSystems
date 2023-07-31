/* Indica que aparece en pantalla al ejecutar este programa.
 * Justifica la respuesta
 * */
//JosÈ Manuel PÈrez Lobato

#include <stdio.h>
#include <unistd.h>

int main () {
  int a=3,pid;
  
  printf ("Hola\n");
  pid=fork();
  printf ("Adios\n");
}
