#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {

   int v[10];
   int suma=0;
   int i;

   for (i=0; i<10; i++)
	v[i] = atoi(argv[1]);

  
   for (i=0; i<10; i++)
	suma = suma + v[i];
   printf ("Suma elementos for = %d \n", suma);

   i=0;
   suma=0;
   while (i<10){
	suma = suma + v[i];
        i++;
   }
   printf ("Suma elementos while = %d \n", suma);
}
