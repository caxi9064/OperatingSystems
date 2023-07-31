

/*
Write a C program that creates three processes. Two of them write the standard output in a pipe and the third reads the standard input from the pipe. 
*/

 

#include <stdio.h>
int main( void ) 
{ 
    int my_pipe[2];
	int pid1, pid2;
    /* Processp1 is the parent and creates the pipe */
 	if (pipe(my_pipe) < 0) {
        perror(ÒError: I canÕt create the pipeÓ) ;
        exit(0);
    }
    /* Processp2 */
switch ((pid1=fork()) {
        case -1: perror(ÒError creating new process Ó) ;
                 /* pipe closed */
                 close(my_pipe[0]) ;
                 close(my_pipe[1]) ;
             exit(0) ;
                 break ;
  	case 0: /* Processchild, ProcessB */
                /* close read pipe */
                close(my_pipe[0]) ;
                /* code of ProcessB */
            /* code for writting in the pipe using my_pipe[1] */
                break ;
        default: /* ProcessC creation*/
                 switch ((pid2 = fork()) {
                     case -1: perror(ÒError creating new process Ó) ;
                              close(Pipe[0]) ;
                              close(Pipe[1]) ;
                              /* The previous process is killed*/
                              kill(pid1, SIGKILL) ; 
                              exit(0) ;
                     case 0:  /* Processchild (C) reads from pipe */
                              close(Pipe[1]) ;
                              /* code for reading from the pipe*/
                              break ; 
                     default: /* parent (B) writes in the pipe */
                              close(my_pipe[0]) ;
                              /* code for writing in the pipe*/
                          break ;
                 }
}


