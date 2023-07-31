#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define		NUM 	10
int cont=0;

void manejador_ctrlc (int s){
  	printf ("Ha llegado la seÒal de alarma: %d\n",s);
	cont++;
	if(cont==NUM)
		raise(SIGABRT);
}

int main (){
	struct sigaction sa;

	sa.sa_handler= manejador_ctrlc;
	sa.sa_flags=0;
	sigemptyset (&(sa.sa_mask));
	sigaction (SIGINT, &sa, NULL);

	for(;;){
		pause();
	}
	exit(0);
}

