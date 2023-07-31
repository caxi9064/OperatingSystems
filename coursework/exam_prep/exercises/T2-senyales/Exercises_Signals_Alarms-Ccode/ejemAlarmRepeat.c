#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void manejador_alarma (int s){
  	printf ("Ha llegado la señal de alarma: %d\n",s);
}

int main (){
	struct sigaction sa;

	sa.sa_handler= manejador_alarma;
	sa.sa_flags=0;
	sigemptyset (&(sa.sa_mask));
	sigaction (SIGALRM, &sa, NULL);

	for(;;){
		alarm(10);
		pause();
	}
	exit(0);
}
