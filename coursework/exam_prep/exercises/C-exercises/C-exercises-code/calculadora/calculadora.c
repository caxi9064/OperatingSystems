
/* Calculadora sencilla en varios ficheros*/
//Compilar con gcc principal.c funciones.c 
//JosÈ manuel PÈrez Lobato
#include <stdio.h>

void pedirNumeros(int *num1, int *n2){
  *num1=0;
  *num1=*num1 + 1; // sumamos 1 al valor entero asociado a num1
  printf ("dar un numero\n");
  scanf ("%d",num1);
  printf ("dar otro numero\n");
  scanf ("%d",n2);
}

int sumar (int num1, int n2){
  int res;
  res=num1+n2;
  return res;
}

int restar (int num1, int n2){
  int res;
  res=num1-n2;
  return res;
}

int multiplicar (int num1, int n2){
  int res;
  res=num1*n2;
  return res;
}

int dividir (int num1, int n2, int *coc, int *resto){
  int res=-1;
  if (n2 == 0){
    printf ("Error: divide by 0 \n");
    *coc=-1;
    *resto=-1;
  }
  else {
    *coc=num1/n2;
    *resto=num1%n2;
    res=0;
  }
  return res;
}

char menu(){

  char op;
  printf ("\n==========================\n");
  printf ("Dar operacion :\n");
  printf ("+ -Sumar \n");
  printf ("- -Restar \n");
  printf ("* -Multiplicar \n");
  printf ("/ -Dividir \n");
  printf ("0-fin\n");

  scanf("%c", &op);
  printf("operación: %c\n", op);

  return (op);
}
