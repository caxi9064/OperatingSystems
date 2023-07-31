#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void capturaSenal1 (int s){
	  printf ("Ha llegado la senyal 1: %d\n",s);
	  kill (getpid(), SIGUSR2);
}
void capturaSenal2 (int s){
	  printf ("Ha llegado la senyal 2: %d\n",s);
}

int main (){
   int i;
  struct sigaction sa;

	sa.sa_handler= capturaSenal1;
	sa.sa_flags=0;
	sigemptyset (&(sa.sa_mask));
	sigaction (SIGUSR1, &sa, NULL);
	signal (SIGUSR2, capturaSenal2);
	for  (i=0; i<10; i++){
		sleep(1);
		printf ("%d\n",i);
	
        }
	kill (getpid(), SIGUSR1);
}
