#include <stdio.h>
#include <signal.h>

void llegoAlarma (int s){
	  printf ("Ha llegado la señal de alarma: %d\n",s);
}
main (){
int i,faltan;
struct sigaction sa;

	sa.sa_handler= llegoAlarma;
	sa.sa_flags=0;
	sigemptyset (&(sa.sa_mask));
	sigaction (SIGALRM, &sa, NULL);
	alarm(3);
	for  (i=1; i<=10; i++){
		sleep(1);
		printf ("Han pasado %d seg.\n", i);
		if (i%4== 0) alarm (3);
	}
	faltan=alarm(0);
	printf ("Faltaban %d seg para la siguiente alarma\n",faltan);
}
