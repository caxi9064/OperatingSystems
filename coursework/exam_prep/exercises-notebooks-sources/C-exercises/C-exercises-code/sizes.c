#include <stdio.h>
#include <string.h>

int main (){
  int v[10];
  char cad[12];

  printf ("tamano de vector: %lu, numero de elementos enteros del array= %lu\n",sizeof(v), sizeof(v)/sizeof(int));
  printf ("tamano de cad:%lu, numero de posiciones del array=%lu\n",sizeof(cad),sizeof(cad)/sizeof(char));
  printf ("longitud de cad:%lu\n",strlen(cad));
  strcpy (cad,"Hola Ana");
  printf ("Copia. Nuevo tamano de cad:%lu, numero de posiciones del array=%lu\n",sizeof(cad),sizeof(cad)/sizeof(char));
  printf ("longitud de cad:%lu\n",strlen(cad));

}

