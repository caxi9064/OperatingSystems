/*
 * Programa que pide una serie de cadenas de caracteres y cuenta
 * el n˙mero de blancos y el n˙mero total de caracteres
 * JosÈ Manuel PÈrez Lobato
 */
#include <stdio.h>
#include <string.h>
#define NUMCADENAS 5
#define TAMCADENAS 80

void leerCadenas (char vs[][TAMCADENAS]);
void escribirCadenas (char vs[][TAMCADENAS]);
int contarCaracteres (char vs[][TAMCADENAS]);
int contarBlancos (char vs[][TAMCADENAS]);

int main(){
  char vs[NUMCADENAS][TAMCADENAS];

  leerCadenas (vs);
  escribirCadenas(vs);
  printf ("total caracteres en el array de cadenas= %d \n", 
  	contarCaracteres (vs) );
  printf ("total blancos en el array de cadenas= %d \n", 
  	contarBlancos (vs) );
}
void leerCadenas (char vs[][TAMCADENAS]){
  int i;

  for (i=0; i<NUMCADENAS; i++) {
    printf ("Dar cadena posicion %d :", i);
    fgets (vs[i], TAMCADENAS, stdin);
    /* otra forma de lectura :scanf ("%s", vs[i]); */
  }
}

void escribirCadenas (char vs[][TAMCADENAS]){
  int i;

  for (i=0; i<NUMCADENAS; i++) 
    printf ("La cadena de posicion %d  vale :%s:\n", i,vs[i]);
}
int contarCaracteres (char vs[][TAMCADENAS]){
  int i,cont=0;

  for (i=0; i<NUMCADENAS; i++) 
    cont= cont + strlen (vs[i]);
  return cont;
}
int contarBlancos (char vs[][TAMCADENAS]){
  int i,j,cont=0;

  for (i=0; i<NUMCADENAS; i++) 
    for (j=0; j<strlen(vs[i]); j++) 
      if (vs[i][j] ==' ')
        cont= cont + 1;
  return cont;
}

