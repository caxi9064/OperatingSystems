#include <stdio.h>
#include <stdlib.h>


float sumar (float a, float b){

 return(a+b);
}

int main (int argc, char **argv) {

   float n1, n2, suma;

   n1 = atof(argv[1]);
   n2 = atof(argv[2]);

   suma = sumar(n1, n2); 
  
   printf ("Suma = %.3f \n", suma);
}
