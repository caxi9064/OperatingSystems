#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "registro.h"

#define N 4


int main ( int argc, char *argv[] ) 
{
	int file1 ;
	int i ;
	tipoRegistro registro1 ;
	int posicion1 ;
	char nombreFich[30]="registros.dat" ;


	/* Abrir fichero */
        file1 = open (nombreFich,O_APPEND|O_WRONLY) ;
	if (-1 != file1) {
	  printf ("El fichero ya existe, anyado al final\n");
	}

	if (-1 == file1) {
	  printf ("El fichero no existe\n");
	  printf ("Se va a crear el fichero\n");
          file1=open (nombreFich, O_CREAT| O_WRONLY, S_IWUSR|S_IRUSR) ;
	  if (-1 == file1) {
	      printf ("Error en la creacion :1\n");
	      exit (-1);
	  }
	}

	/* Escribir registros */
        registro1.codigo=0;
        for (i=1; i< N; i++) {

	    registro1.codigo++;
	    strcpy (registro1.nombre, "nombre dos");
	    write (file1, &registro1, sizeof (registro1) );
        }

	/* Imprimir la posición */
        posicion1 = lseek(file1,0,SEEK_CUR) ;
        printf ("Estoy en la posicion %d del fichero\n", posicion1 );

	/* Cerrar fichero */
	close(file1);
}

