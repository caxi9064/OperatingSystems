#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#define		CONT	4
int main(int argc, char** argv){
	int num;
	int cont=0;

	if (argc!=2)
	{
		printf("Error: uso <%s> <NUM>\%d", argv[0]);
		exit(-1);
	}
	
	num=atoi(argv[1]);
	while(cont<CONT){
		printf("%d\n",num);
		cont++;
	}
}

