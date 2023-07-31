/* Juan Manuel Lobato */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "registro.h"

int main ( int argc, char *argv[] ) 
{
	int file1;
	int bytes_leidos;
	char nombreFich[40]="registros.dat";
	tipoRegistro registro1;


	file1 = open (nombreFich, O_RDONLY) ;
	if (file1 == -1) {
    	    fprintf (stderr, "No se ha podido abrir el fichero\n");
	    exit (-1) ;
        }

	bytes_leidos = read (file1, &registro1, sizeof(registro1));
	while ( bytes_leidos !=0 ){
	        printf  ("registro leido -> codigo:%d: nombre:%s:\n",
			 registro1.codigo, 
			 registro1.nombre);
	        bytes_leidos = read (file1, &registro1, sizeof(registro1));
       	}		

	close(file1);
}


