

/*Este programa crea 5 hijos*/

#include <stdio.h>
#include <stdlib.h>

int main (){
  int i,pid;
  for (i=1; i<=5; i++){
    pid=fork ();
    if ( pid==0){
       printf ("Hijo %d ( pid=%d)\n",i,getpid());
       exit (0); //return(0);
    }
    else; 
	  // El padre no tiene nada mas que hacer
  }
  /* El padre finaliza sin esperar a los hijos que se quedan sin padre (zombies)
}

