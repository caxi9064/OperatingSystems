#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(){
    int p[2];
    int status;
    int i;
    char c;

    pipe(p);

    for (i=0;i<2;i++) {
	if (fork() == 0) {
	    if (i == 0) {
		close(p[0]);
		printf ("Child %d sleeps 2 secs\n",getpid());
		sleep(2);
		c = 'a';
		printf ("Child %d start writing character '%c' to pipe\n", getpid(), c);
		if (write(p[1],&c,1) < 0)
			perror("Child write to pipe");
		exit(0);
	    }
	    else {
		close(p[1]);
		printf ("Child %d start reading from pipe\n", getpid());
		if (read(p[0],&c, 1)< 0) 
			perror("Child read from pipe");
		else
			printf("Child %d read c=%c\n", getpid(),c);
		exit(0);
	    }   	    
	} 
	else {
	    if (i == 0) {
	      //close(p[0]); 
	      close(p[1]);  
	    }
	    else {
	      close(p[0]);
	      close(p[1]);
	    }
	}
    }
    
    printf ("Father waiting for the children to terminate\n");
    for (i=0; i<2; i++)
      wait(&status);
    return 0;
}
