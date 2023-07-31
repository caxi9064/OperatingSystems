/*Ejemplo de utilización de las tuberías*/
//José Manuel Pérez Lobato

#include	<stdio.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<stdlib.h>

#define ESPERALECTURA 1
#define ESPERAESCRITURA 2

int main () {
	int 		fd[2];
	pid_t		pid_hijo;
	char		cadena [] ="Hola soy el hijo.\n";
	char		buffer [80];
	int		num_bytes_leidos;

	/* Establecemos la tuberia  */
	pipe (fd);

	if ((pid_hijo = fork ())== -1) {
	  perror ("fork");
	  exit (1);
	}
	if (pid_hijo == 0 ) {
           /* El hijo cierra el descriptor de entrada */
	  close (fd[0]);
           /* El hijo escribe en la tuberia */
	  sleep (ESPERAESCRITURA);
          write (fd[1], cadena, sizeof (cadena));
	  printf ("Fin escritura\n");
	  exit (0);
	}
	else { /* El padre cierra el descriptor de salida */
	  close (fd[1]);
	  /* El padre lee de la tuberia */
  	  sleep (ESPERALECTURA);
	  num_bytes_leidos = read (fd[0], buffer, sizeof (buffer));
	  printf ("La cadena recibida por el padre es:%s:", buffer);
	}
	return (0);
}

