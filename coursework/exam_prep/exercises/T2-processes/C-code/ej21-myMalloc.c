#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define	MAX_SIZE	(1024*1024)	/* 1 MB */
#define	N		10		/* Number of times */

int main(){
	char *buffer[N]; 
	int i=0;
	char car;

	for(i=0;i<N;i++){
		buffer[i]=(char*) malloc(MAX_SIZE);
		memset(buffer[i],'a',MAX_SIZE);
		if (buffer[i] == NULL){
			printf("Error with malloc...\n");
			exit(-1);
		}else{
			printf("%d - Block of %d bytes allocated\n", i, MAX_SIZE);
		}
		sleep(10);
	} 

	printf("Press any key to exit...\n");
	scanf("%c",&car);

	for(i=0;i<N;i++){
		free(buffer[i]);
	} 
	exit(0);
}
