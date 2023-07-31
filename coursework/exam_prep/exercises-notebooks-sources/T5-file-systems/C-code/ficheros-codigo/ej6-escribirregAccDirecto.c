#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "registro.h"

/*
Programa que pide un código/posición de persona y escribe los datos en laposición del fichero que corresponden
*/
int main () {
	int f;
	int numbyteescritos;
	tipoRegistro reg;
	char nombreFich[30]="registros.dat";
        mode_t mode = S_IRUSR | S_IWUSR;

        /*  Tratamos de abrir el fichero.  Si no existe se crea  */
        if ((f=open (nombreFich, O_WRONLY|O_CREAT, mode)) == -1) {
	  perror ("Error en la apertura del fichero \n");
	  exit (-1);
	}

  	  printf( "Dar codigo del usuario:");
 	  scanf ("%d", &reg.codigo);
  	  printf( "Dar nombre del usuario:");
 	  scanf ("%s", &reg.nombre);

	//resto -1 porque la persona de código n está en la posición n-1
          lseek (f, (reg.codigo-1) * sizeof (reg), SEEK_SET); 
	  numbyteescritos=write (f, &reg, sizeof (reg) );
         if (numbyteescritos == -1)
	  printf  ("Error al escribir registro codigo:%d\n",reg.codigo);
         else
	  printf  ("registro escrito,  codigo:%d: nombre:%s:\n",reg.codigo, reg.nombre);

	  close(f);
}


