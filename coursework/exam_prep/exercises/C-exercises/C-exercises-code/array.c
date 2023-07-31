#include <stdio.h>

#define DIM 5

int main  () {
    
    int i, v[DIM];

    for (i=0; i<DIM; i++) {
      printf ("Dar valor:");
      scanf ("%d", &v[i]);
    }
    for (i=0; i<DIM; i++) 
      printf ("Valor de la posicion %d es %d:\n",i, v[i]);

}
