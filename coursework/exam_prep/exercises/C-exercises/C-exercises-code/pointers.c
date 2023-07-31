/* Prueba malloc y free 
  Direcciones y contenido de punteros
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main  () {

    int *x;
    int *y;
   
    char* tira;

    printf ("Direccion de x  %p\n", x);
    x = malloc (sizeof(int));
    printf ("Malloc. Direccion de x  %p\n", x);
    *x = 4;
    printf ("Contenido de  x  %d\n", *x);
    free(x);
    printf ("Direccion de y  %p\n", y);
    printf ("Contenido de  y  %d\n", *y);
    *y = 5;
    printf ("Coontenido de  y  %d\n", *y);

    printf ("Direccion de tira  %p\n", tira);
    tira = malloc (10);
    printf ("Direccion de tira  %p\n", tira);
    strcpy(tira, "prueba");
    printf ("Contenido de tira  %s\n", tira);
}
