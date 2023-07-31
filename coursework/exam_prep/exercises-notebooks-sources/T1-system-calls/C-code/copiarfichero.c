#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE		512			/*tamaño de las tiras a leer*/
#define PERM 		0644		/*permisos para creación de archivo*/

int copyfile (char *name1, char *name2)	/*copia file name1 a file name2*/
{
	int infile, outfile, nread;
	char buffer [BUFSIZE];
	if ( (infile = open(name1, O_RDONLY) ) < 0 )
		return(-1); /* no puede abrirse */
	if ( (outfile = creat (name2, PERM) ) < 0 ) {
		close (infile);
		return (-2); /* no puede crearse */
		}
	/*lectura de name1 BUFSIZE caracteres de una vez*/
	while( (nread = read(infile, buffer, BUFSIZE) ) > 0 )
	{
		/*escribir el buffer al archivo de salida*/
		if (write (outfile, buffer, nread) < nread)
		{
			close(infile);
			close(outfile);
			return (-3); 			/* error al escribir */
		}
	}
	if (nread==-1)
		return (-4); 	/* error al leer */
	close(infile);
	close(outfile);
	return(0);
}

int main (int argc, char ** argv) {

   int res;

   res=copyfile(argv[1], argv[2]);

   switch(res){
       case(-1):
	printf("source file cannot be open\n");
        break;
       case(-2):
	printf("destination file cannot be created\n");
        break;
       case(-3):
	printf("destination file cannot be writen\n");
        break;
       default:
	printf("file %s copied to file %s\n", argv[1], argv[2]);
    }

}

