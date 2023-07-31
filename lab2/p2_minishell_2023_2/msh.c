//P2-SSOO-22/23

// MSH main file
// Write your msh source code here

//#include "parser.h"
#include <stddef.h>			/* NULL */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>

#define MAX_COMMANDS 8


// files in case of redirection
char filev[3][64];

//to store the execvp second parameter
char *argv_execvp[8];


void siginthandler(int param)
{
	printf("****  Exiting MSH **** \n");
	//signal(SIGINT, siginthandler);
	exit(0);
}


/* Timer */
pthread_t timer_thread;
unsigned long  mytime = 0;

void* timer_run ( )
{
	while (1)
	{
		usleep(1000);
		mytime++;
	}
}

/**
 * Get the command with its parameters for execvp
 * Execute this instruction before run an execvp to obtain the complete command
 * @param argvv
 * @param num_command
 * @return
 */
void getCompleteCommand(char*** argvv, int num_command) {
	//reset first
	for(int j = 0; j < 8; j++)
		argv_execvp[j] = NULL;

	int i = 0;
	for ( i = 0; argvv[num_command][i] != NULL; i++)
		argv_execvp[i] = argvv[num_command][i];
}


/**
 * Main sheell  Loop  
 */
int main(int argc, char* argv[])
{
	/**** Do not delete this code.****/
	int end = 0; 
	int executed_cmd_lines = -1;
	char *cmd_line = NULL;
	char *cmd_lines[10];

	if (!isatty(STDIN_FILENO)) {
		cmd_line = (char*)malloc(100);
		while (scanf(" %[^\n]", cmd_line) != EOF){
			if(strlen(cmd_line) <= 0) return 0;
			cmd_lines[end] = (char*)malloc(strlen(cmd_line)+1);
			strcpy(cmd_lines[end], cmd_line);
			end++;
			fflush (stdin);
			fflush(stdout);
		}
	}

	pthread_create(&timer_thread,NULL,timer_run, NULL);

	/*********************************/

	char ***argvv = NULL;
	int num_commands;


	while (1) 
	{
		int status = 0;
		int command_counter = 0;
		int in_background = 0;
		signal(SIGINT, siginthandler);

		// Prompt 
		write(STDERR_FILENO, "MSH>>", strlen("MSH>>"));

		// Get command
		//********** DO NOT MODIFY THIS PART. IT DISTINGUISH BETWEEN NORMAL/CORRECTION MODE***************
		executed_cmd_lines++;
		if( end != 0 && executed_cmd_lines < end) {
			command_counter = read_command_correction(&argvv, filev, &in_background, cmd_lines[executed_cmd_lines]);
		}
		else if( end != 0 && executed_cmd_lines == end) {
			return 0;
		}
		else {
			command_counter = read_command(&argvv, filev, &in_background); // NORMAL MODE
		}
		//************************************************************************************************
		/************************ STUDENTS CODE ********************************/
		if (command_counter > 0) {
			if (command_counter > MAX_COMMANDS){
				printf("Error: Maximum number of commands is %d \n", MAX_COMMANDS);
			}
			else {
				// check for background execution
				int in_background = 0;
				if (strcmp((const char *)argvv[command_counter-1], "&") == 0){
					in_background = 1;
					command_counter--; // remove "&" from the command list
				}
				
				getCompleteCommand(argvv, 0); // get arguments for execvp
				int num_pipes = command_counter - 1; 
				if (num_pipes > 0) { // check for piping
					int fd[num_pipes*2];
					for (int i = 0; i < num_pipes; i++){ // create pipes
						if (pipe(fd + i*2) < 0){ 
							perror("pipe() error");
							exit(-1);
						}
					}
					pid_t pid; // fork child processes 
					for (int i = 0; i < command_counter; i++){
						pid = fork();
						if (pid < 0){ // error
							perror("fork() error");
							exit(-1);
						}
						else if (pid == 0){ // child process
							if (i != 0){ // not the first command, connect input to the pipe
								if (dup2(fd[(i-1)*2], STDIN_FILENO) < 0){
									perror("dup2() error");
									exit(-1);
								}
							}
							if (i != command_counter-1){ // not the last command, connect output to the pipe
								if (dup2(fd[i*2+1], STDOUT_FILENO) < 0) {
									perror("dup2() error");
									exit(-1);
								}
							}
							for (int j = 0; j < num_pipes * 2; j++){ // close all pipe ends
								close(fd[j]);
							}
							getCompleteCommand(argvv, i); // Execute the command
							if (execvp(argv_execvp[0], argv_execvp) == -1) {
								perror("execvp() error");
								exit(EXIT_FAILURE);
							}
						}
					}
					// Parent process
					for (int i = 0; i < num_pipes * 2; i++) {
						close(fd[i]);
					}
					for (int i = 0; i < command_counter; i++) {
						wait(&status);
					}
				} 
				else { // no piping
					pid_t pid, pid_wait;
					int wstatus;
					pid = fork(); //fork a new process
					switch(pid){
						case -1: // failed
							perror("fork() error");
							exit(-1);
							break;
						case 0: // child process, going to execute 
							execvp(argv_execvp[0], argv_execvp);
							perror("execvp: ");
							exit(-1);
							break;
						default: // parent, is going to wait for the child
							if (!in_background){
								do{
									pid_wait = wait(&wstatus);
									if (pid_wait == -1) {
										perror("wait() error");
										exit(-1);
									} 
								} while (pid_wait != pid);
							}
							break;
					}
					/*
					if (pid < 0) {
						perror("fork() error");
					}
					else if (pid == 0) {
						// Child process

						// Execute the command
						if (execvp(argv_execvp[0], argv_execvp) == -1) {
							perror("execvp() error");
							exit(EXIT_FAILURE);
						}

						// Should never reach this point
						exit(EXIT_SUCCESS);
					}
					else {
						// Parent process
						int status;
						if (in_background == 0) {
							waitpid(pid, &status, 0);
						}
					}
					*/
				}
			}
		}
	}
	return 0;
}