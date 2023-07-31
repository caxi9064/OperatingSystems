#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	pid_t pidHijo;
	int status;
	
	pidHijo=fork();
	switch (pidHijo){
		case -1: printf ("Error fork()\n");
			 break;
		case 0:  /* proceso hijo */
		 	printf("Proceso hijo - pid=%d\n", getpid());
			sleep(10);
			break;
		default: /* proceso padre */
		 	printf("Proceso padre - pid=%d\n", getpid());
		 	//wait(&status); 
		 	exit(0);
		 	if (status==0){
		 		printf("Hijo termino OK\n");
		 	}else{
		 		printf("Hijo termino KO\n");
		 	}
	}
	return 0;
}


