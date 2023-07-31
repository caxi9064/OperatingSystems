/* este programa de ejemplo de uso de las tuberías sirve para ver como 2 programas (prog_esc y prog_lec) que por defecto utilizan la salida y la entrada estandar para escribir o leer los datos que utilizan pueden comunicarse a través de una
tubería creada por el padre de ambos procesos.
El programa prog_esc.c debe compilarse con gcc -o prog_esc prog_esc.c
El programa prog_lec.c debe compilarse con gcc -o prog_lec prog_lec.c
*/
//José Manuel Pérez Lobato

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/types.h>

int main () {
	int 		fd[2];
	pid_t		pid_hijo;
	/* Establecemos la tuberia  */
	pipe (fd);
	if ((pid_hijo = fork ())== -1) {
		perror ("fork");
		exit (1);
	}
	if (pid_hijo == 0 ) { /* el hijo */
	/*  Cambio la salida estándar por la de la tuberia */
		dup2 (fd[1],1);
		close (fd[0]);
	/* prog_esc escribe sobre la salida estándar, que sera la tuberia */
		execlp ("./prog_esc", "./prog_esc", NULL);
	}
	else { /* padre*/
	/*  Cambio la entrada estándar por la de la tuberia */
		dup2 ( fd[0],0);
		close (fd[1]);
	/* prog_lec lee de la entrada estándar, que sera la tuberia */
		execlp ("./prog_lec", "./prog_lec", NULL);
	}
	return (0);
}

