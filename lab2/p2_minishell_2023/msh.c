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
#define MAX_ARGS 10

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
				// Initialize environment variable Acc to 0
				setenv("Acc", "0", 1);
				// Store start time of minishell in milliseconds
				struct timeval start_time;
				gettimeofday(&start_time, NULL);
				long int start_millis = start_time.tv_sec * 1000 + start_time.tv_usec / 1000;

				//setenv("mytime", ltoa(start_millis, 10), 1); 
				char acc_millis[32];
				snprintf(acc_millis, sizeof(acc_millis), "%d", start_millis);
				setenv("mytime", acc_millis, 1);
				
				// Handle internal commands
				if (strcmp(argvv[0][0], "mycalc") == 0) {
					// Check number of arguments
					
					if (sizeof(argvv[0]) < 4) {
						fprintf(stderr, "[ERROR] The structure of the command is mycalc <operand 1> <add/mul/div> <operand 2>\n");
						continue;
					}
					// Parse operands
					int operand1 = atoi(argvv[0][1]);
					int operand2 = atoi(argvv[0][3]);

					// Perform operation
					if (strcmp(argvv[0][2], "add") == 0) {
						int acc = atoi(getenv("Acc"));
						acc += operand1 + operand2;
						//setenv("Acc", itoa(acc, 10), 1);
						char acc_str[32];
						snprintf(acc_str, sizeof(acc_str), "%d", acc);
						setenv("Acc", acc_str, 1);
						fprintf(stderr, "[OK] %d + %d = %d ;Acc %d\n", operand1, operand2, operand1 + operand2, acc);
					} else if (strcmp(argvv[0][2], "mul") == 0) {
						fprintf(stderr, "[OK] %d * %d = %d\n", operand1, operand2, operand1 * operand2);
					} else if (strcmp(argvv[0][2], "div") == 0) {
						fprintf(stderr, "[OK] %d / %d = %d ;Remainder %d\n", operand1, operand2, operand1/operand2, operand1 % operand2);
					} else {
						fprintf(stderr, "[ERROR] The structure of the command is mycalc <operand 1> <add/mul/div> <operand 2>\n");
						continue;
					}
				}
				else if (strcmp(argvv[0][0], "mytime") == 0) {
					// Calculate elapsed time in milliseconds
					struct timeval current_time;
					gettimeofday(&current_time, NULL);
					long int current_millis = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
					long int elapsed_millis = current_millis - start_millis;
					int elapsed_sec = elapsed_millis / 1000;
					int hours = elapsed_sec / 3600;
					int minutes = (elapsed_sec % 3600) / 60;
					int seconds = elapsed_sec % 60;
					fprintf(stderr, "%02d:%02d:%02d\n", hours, minutes, seconds); // Convert elapsed time to HH:MM:SS format
				
				}

				// check for background execution
				int in_background = 0;
				if (strcmp((const char *)argvv[command_counter-1], "&") == 0){
					in_background = 1;
					command_counter--; // remove "&" from the command list
				}
				// check for simple commands with input + output redirection
				int err_redirect = 0, in_redirect = 0, out_redirect = 0;
				char* in_file = NULL, *out_file = NULL, *err_file = NULL;
				if (in_background == 1){ // need to include????
					for (int i = 0; i < command_counter; i++){
						int arg_counter = 0;
						while (argvv[i][arg_counter] != NULL) {
							if (strcmp((const char *)argvv[i][arg_counter], "<") == 0) { // input redirection
								in_redirect = 1;
								in_file = filev[0];
								argvv[i][arg_counter] = NULL;
								arg_counter += 2;
							}
							else if (strcmp((const char *)argvv[i][arg_counter], ">") == 0) { // output redirection
								out_redirect = 1;
								out_file = filev[1];
								argvv[i][arg_counter] = NULL;
								arg_counter += 2;
							}
							else if (strcmp((const char *)argvv[i][arg_counter], "2>") == 0) { // error redirection
								err_redirect = 1;
								err_file = filev[2];
								argvv[i][arg_counter] = NULL;
								arg_counter += 2;
							}
						}
					}
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
					if (!in_background){
						for (int i = 0; i < command_counter; i++) {
						wait(&status);
						}
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
							// redirect input
							if (in_redirect != 0) {
								int fd_in = open(in_file, O_RDONLY);
								if (fd_in < 0) {
									perror("open() error");
									exit(-1);
								}
								if (dup2(fd_in, STDIN_FILENO) < 0) {
									perror("dup2() error");
									exit(-1);
								}
								close(fd_in);
							}
							// redirect output
							if (out_redirect != 0) {
								int fd_out = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
								if (fd_out < 0) {
									perror("open() error");
									exit(-1);
								}
								if (dup2(fd_out, STDOUT_FILENO) < 0) {
									perror("dup2() error");
									exit(-1);
								}
								close(fd_out);
							}
							// redirect error
							if (err_redirect != 0) {
								int fd_err = open(err_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
								if (fd_err < 0) {
									perror("open() error");
									exit(-1);
								}
								if (dup2(fd_err, STDERR_FILENO) < 0) {
									perror("dup2() error");
									exit(-1);
								}
								close(fd_err);
							}
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

// void my_calc(char **args) {
//     // Check if there are enough arguments
//     if (args[1] == NULL || args[2] == NULL || args[3] == NULL) {
//         fprintf(stderr, "mycalc: not enough arguments\n");
//         return;
//     }

//     int op1 = atoi(args[1]);
//     int op2 = atoi(args[3]);
//     int result;

//     if (strcmp(args[2], "sum") == 0) {
//         result = op1 + op2;
//         char acc_str[100];
//         char *prev_acc = getenv("Acc");
//         int prev_val = prev_acc ? atoi(prev_acc) : 0;
//         int new_val = prev_val + result;
//         snprintf(acc_str, sizeof(acc_str), "%d", new_val);
//         setenv("Acc", acc_str, 1);
//     } else if (strcmp(args[2], "mul") == 0) {
//         result = op1 * op2;
//     } else if (strcmp(args[2], "div") == 0) {
//         if (op2 == 0) {
//             fprintf(stderr, "mycalc: division by zero\n");
//             return;
//         }
//         int quotient = op1 / op2;
//         int remainder = op1 % op2;
//         printf("%d %d\n", quotient, remainder);
//         return;
//     } else {
//         fprintf(stderr, "mycalc: invalid operator '%s'\n", args[2]);
//         return;
//     }

//     printf("[OK] %d\n", result);
// }

// // Function to execute mytime command
// void my_time() {
//     clock_t uptime = clock() / CLOCKS_PER_SEC;
//     int hours = uptime / 3600;
//     int minutes = (uptime % 3600) / 60;
//     int seconds = uptime % 60;
//     fprintf(stderr, "mytime: %02d:%02d:%02d\n", hours, minutes, seconds);
// }