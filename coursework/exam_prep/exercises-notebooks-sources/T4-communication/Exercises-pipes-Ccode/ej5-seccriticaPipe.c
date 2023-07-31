//Ejercicio de las transparencias sobre el uso de las tuberías
// Implemntación de na sección crítica con pipes

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int  main(void) {
   int fildes[2];   /* pipe para sincronizar */
   char c;          /* caracter para sincronizar */

   pipe(fildes);
   write(fildes[1], &c, 1);   /* necesario para entrar en la seccion critica la primera vez */
   if (fork() == 0)  {   	/* proceso hijo */
	    for(;;) {
	      read(fildes[0], &c, 1);  /* entrada seccion critica */
              // Seccion critica 
              printf ("El hijo entra en seccion critica\n");
	      sleep (2);  //espero para que se vea que el padre no entra
              printf ("El hijo sale de la seccion critica\n");
              write(fildes[1], &c, 1);  /* salida seccion critica */
	      sleep (random()%2); //Espero para que no siempre entre el mismo
            } 
    } else {            /* proceso padre */
     	 for(;;) {
           read(fildes[0], &c, 1);   /* entrada seccion critica */
           // Seccion critica 
              printf ("El padre entra en seccion critica\n");
	      sleep (2);  //espero para que se vea que el hijo no entra
              printf ("El padre sale de la seccion critica\n");
           write(fildes[1], &c, 1);  /* salida seccion critica */
	   sleep (random()%2); //Espero para que no siempre entre el mismo
	  }
   }
}
