#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	pid_t pidHijo;
	int miPid;
	char cadena1[8]; 
	int status;
	
	pidHijo=fork();
	switch (pidHijo){
		case -1: printf ("Error fork()\n");
			 break;
		case 0:  /* proceso hijo */
			miPid=getpid();
		 	printf("Proceso hijo - pid=%d\n", getpid());
			sprintf(cadena1, "%d", miPid); 
			execlp("./hijo", "hijo", cadena1, NULL);
			exit(-1);
		default: /* proceso padre */
		 	printf("Proceso padre - pid=%d\n", getpid());
		 	wait(&status); 
	}
	return 0;
}


