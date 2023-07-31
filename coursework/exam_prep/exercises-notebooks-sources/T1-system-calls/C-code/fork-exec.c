#include <unistd.h>
#include <stdio.h>

int main() 
{ 
	int valor_regr=0;
                
	printf("Bifurcando el proceso\n");

	valor_regr=fork();

	printf("El id del proceso es %d y el valor devuelto es %d\n",
		getpid(), valor_regr);

	execl("/bin/ls","ls","-l",0);

	printf("Esta linea no es impresa\n");
}

