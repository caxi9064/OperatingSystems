/* Este programa muestra en pantalla la lista de par·metros que recibe.
 * Compilar con 
 *   gcc -o  parametrosmain parametrosmain.c
 * ejecutar con 
 *   parametrosmain uno dos Juan
 */
//JosÈ Manuel PÈrez Lobato

#include <stdio.h>
int main (int argc, char *argv[]) {
  int i;
  printf ("numero de par·metros : %d\n", argc);
  printf ("Lista de parametros\n" );
  for (i=0; i< argc; i++)  
    printf ("parametro %d = %s\n", i, argv[i]);
}
