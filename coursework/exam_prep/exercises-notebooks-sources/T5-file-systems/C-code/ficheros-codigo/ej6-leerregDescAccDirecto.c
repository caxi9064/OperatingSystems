#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "registro.h"

/*
Programa que pide un código/posición de persona y muestra los datos que se encuentran en esa posición  en el fichero 
*/
int main () {
	int f;
	int numbyteleidos,cod;
	char nombreFich[40]="registros.dat";
	tipoRegistro reg;

	if ((f=open (nombreFich, O_RDONLY)) == -1)
    	  fprintf (stderr, "No se ha podido abrir el fichero\n");
	else {
  	  printf( "Dar codigo del usuario:");
 	  scanf ("%d", &cod);
	//resto -1 porque la persona de código n está en la posición n-1
          lseek (f, (cod-1) * sizeof (reg), SEEK_SET); 
	  numbyteleidos=read (f, &reg, sizeof(reg));
	  printf  ("registro leido,  codigo:%d: nombre:%s:\n",reg.codigo, reg.nombre);
	  close(f);
        }		
}


