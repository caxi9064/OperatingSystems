#include <stdio.h>
#define PI 3.14

/* Este es el primer programa 
   para ver el funcionamiento del printf con números */
int main () {
  int v,v2;
  float f;
  v=33;  // le damos un valor inicial a la v
  v2=22;
  f = PI;
  printf ("valor de v = %d, valor de v2 = %d valor de f = %f \n",v, v2, f);
  printf("\nNow an error due data format not defined\n"); 
  printf ("valor de v=, valor de v2 %d valor de f = %f  \n",v, v2, f);

}

