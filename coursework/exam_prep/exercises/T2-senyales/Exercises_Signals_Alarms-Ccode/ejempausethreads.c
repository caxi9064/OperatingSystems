#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>

#define		NUM 3	

void manejador_ctrlc (int s){
  	printf ("Ha llegado la seÒal %d al proceso hijo =%d\n",s,pthread_self());
	pthread_exit(0);	
}

int funcion(){
	for(;;){
	}
}
main (){
	int i;
	pid_t pid;
	int status;
	char tecla;
	pthread_t th[NUM];
	struct sigaction sa;

	sa.sa_handler= manejador_ctrlc;
	sa.sa_flags=0;
	sigemptyset (&(sa.sa_mask));
	sigaction (SIGINT, &sa, NULL);

	for(i=0;i<NUM;i++){
		pthread_create(&th[i],NULL,(void*)funcion,NULL);
	}
	for(i=0;i<NUM;i++){
		printf("Envio seÒal %d a proceso %d\n", SIGINT, th[i]);
		pthread_kill(th[i], SIGINT);
	}
	printf("pulsa tecla\n");
	scanf("%c",&tecla);
	for(i=0;i<NUM;i++){
		pthread_join(th[i],NULL);
	}
	exit(0);
}
