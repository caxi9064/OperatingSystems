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
			execlp("/bin/ls", "ls", "-la", "-s", NULL);
			exit(-1);
		default: /* proceso padre */
		 	printf("Proceso padre - pid=%d\n", getpid());
		 	wait(&status); 
	}
	return 0;
}


