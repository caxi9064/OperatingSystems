#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void capturaSenal1 (int s){
	  printf ("Señal recibida en el hijo: %d\n",s);
}

int main (){
  int i, pid;
  struct sigaction sa1,sa2;

  pid = fork();
  if (pid != 0){
      sleep (10);
      kill (pid, SIGUSR1);
      exit(0);
}
  else { //hijo
    sa1.sa_handler=capturaSenal1;
    sa1.sa_flags=0;
    sigemptyset(&(sa1.sa_mask));
    sigaction (SIGUSR1, &sa1,NULL);

    pause(); // == sleep(999999)
   }
}

