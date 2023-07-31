/* este programa espera 3 seg a que el usuario pulse un número y si no lo hace deja de esperar */
// José Manuel Pérez Lobato 
#include <stdio.h>
#include <signal.h>
int finTiempo=0;
void llegoAlarma (int s){
  printf ("Ha llegado la señal de alarma: %d\n",s);
  finTiempo=1;
}
main (){
int i,faltan,n=33;
struct sigaction sa;

	sa.sa_handler= llegoAlarma;
	sa.sa_flags=0;
	sigemptyset (&(sa.sa_mask));
	sigaction (SIGALRM, &sa, NULL);
	alarm(3);
		printf ("Dar un número (tiene 3 segundos) \n" );
		scanf ("%d",&n);
		if (finTiempo)
		  printf ("Se acabo el tiempo el número  sera el %d\n",n );
		else 
		printf ("número leído %d\n",n );
}
