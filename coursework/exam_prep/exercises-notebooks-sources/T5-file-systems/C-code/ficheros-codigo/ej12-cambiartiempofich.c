/*José Manuel Pérez Lobato
Este programa modifica la fecha de acceso del fich_existente colocandola 2 horas respecto a la fecha actual y modifica la fecha de modificación colocándola 3 horas antes que la que tenía
Se puede comprobar con un ls -l antes y después de la ejecución del programa
*/ 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <utime.h>

int main () {
  int er=0;
  struct stat atributos;
  struct utimbuf tiempo_fich;
  time_t hora_actual;

   
  er =stat ("fich_existente", &atributos);
  if (er!=0) printf ("Error\n");
  else {
    hora_actual =time (&hora_actual);
    /* adelanto la fecha de acceso al fichero 2 horas respecto a la actual*/
   printf ("Hora actual: %d \n", (int)hora_actual);
    tiempo_fich.actime =hora_actual -2*60*60;
   printf ("Cambio hora actual: %d \n", (int)tiempo_fich.actime);
    /* adelanto la fecha de modificación del fichero 3 horas respecto a la que tenía */
    tiempo_fich.modtime=atributos.st_mtime- 3*60*60;
   printf ("Cambio hora modificacion: %d \n", (int)tiempo_fich.modtime);
    utime ("fich_existente", &tiempo_fich);
  }
}
