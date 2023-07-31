#include <stdio.h>
#include <signal.h>

int fin=0;
void llegoAlarma (int s){
	  printf ("Ha llegado la señal de alarma: %d\n",s);
	  fin=1;
}
main (){
int i,suma=0;
struct sigaction sa;

	sa.sa_handler= llegoAlarma;
	sa.sa_flags=0;
	sigemptyset (&(sa.sa_mask));
	sigaction (SIGALRM, &sa, NULL);
	alarm(8);
	for  (i=1; i<=9999999 && !fin ; i++){
	   sleep (1);
	   suma=suma + i;
	}
	printf ("Resultado suma= %d \n",suma);
}
