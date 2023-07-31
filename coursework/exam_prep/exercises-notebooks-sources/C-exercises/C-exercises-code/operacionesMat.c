/*Ejemplo de uso de librerias para calcular la raiz cuadrada
 * compilar con gcc -lm operaciones.c -o operaciones
 */
#include <stdio.h>
#include <math.h>

main () {
  int resto, cociente, numero;
  int dividendo = 256;
  int divisor = 20;
  float rc, div;

  printf (" dividendo = %d, divisor=%d\n", dividendo, divisor);

  if(dividendo % 2 == 0){
    printf("El dividendo es Par\n");
  } else {
    printf("El dividendo es Impar\n");
  }


  cociente = dividendo / divisor;
  resto= dividendo % divisor;

  printf (" resto = %d, cociente=%d\n", resto, cociente);

  rc= sqrt((double)dividendo);
  printf (" dividendo= %d, raíz cuadrada=%f\n", dividendo, rc);

  div = (float)(dividendo) / divisor;

  printf (" division= %f, redondeo superior=%f, redondeo inferior=%f \n", div, ceil(div), floor(div));
  

}
