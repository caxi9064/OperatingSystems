#include <stdio.h>

void intercambiar (int *x, int *y) {
  int r;
  r=*x;
  *x=*y;
  *y=r;
}

int main  () {
  int a=3, b=5;
  printf ("a= %d, b=%d\n", a, b );  //Tiene que aparecer 5 , 3
  intercambiar (&a,&b);
  printf ("intercambiados a= %d, b=%d\n", a, b );  //Tiene que aparecer 5 , 3
}

