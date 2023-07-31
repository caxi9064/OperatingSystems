#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void capturaSenal1 (int s){
	  printf ("Ha llegado la senal: %d\n",s);
          printf ("tiempo:%ld\n", time(NULL));
}
void muerteHijo (int s){
	  printf ("Ha terminado el hijo: %d\n",s);
          printf ("tiempo:%ld\n", time(NULL));
}

int main (){
  int i;
  struct sigaction sa1,sa2;

  if (fork() == 0){
      sleep (10);
      kill ( getppid(), SIGUSR1);
      sleep(3);
  }
  else {
    sa1.sa_handler=capturaSenal1;
    sa1.sa_flags=0;
    sigemptyset(&(sa1.sa_mask));
    sigaction (SIGUSR1, &sa1,NULL);

    sa2.sa_handler=muerteHijo;
    sa2.sa_flags=0;
    sigemptyset(&(sa2.sa_mask));
    sigaction (SIGCHLD, &sa2,NULL);


    pause(); // == sleep(999999)
    pause(); // == sleep(999999)
    printf ("%s \n", "SEÑAL RECIBIDA" );
  }
}

