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
  if (pid==0){ //hijo
    a++;
    printf ("hijo: %d\n",a);
  }
  else {
    sleep(1); 
    printf ("padre: %d\n",a);
  }

}

