
/* José Manuel Pérez Lobato
Este programa recibe un nombre de directorio y  muestra por pantalla los nombres de ficheros y directorios que contiene, su modo, si tienen o no permiso de lectura para el propietario, si son directorios y, para los ficheros modificados en los últimos 10 días muestra su fecha de acceso 
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main () {
int er;
char nomdir[100], nomfich[100], resp[30];
struct stat atr;
DIR *d;
struct dirent *rd1;
time_t fecha;

printf ("Nombre directorio\n");
fgets (nomdir, sizeof (nomdir), stdin);
/* hay que quitar el \n del nombre del directorio*/
nomdir[strlen(nomdir)-1]='\0';

fecha=time(&fecha);
if ((d=opendir(nomdir))==NULL) {
  printf ("No existe ese directorio \n");
  return -1;
}
else {
  while (( rd1 =readdir(d)) != NULL) {
    if ( (strcmp(rd1->d_name, ".")!=0 )&& (strcmp(rd1->d_name, "..")!=0 )){
      strcpy (nomfich, nomdir);
      strcat (nomfich, "/");
      strcat (nomfich, rd1->d_name);
      printf ("fichero :%s:", nomfich);
      er=stat (nomfich, &atr);
      printf ("modo :%#o:", atr.st_mode);
      if ((atr.st_mode & 0400) != 0) 
	 printf (" permiso R para propietario\n");
      else
	 printf (" No permiso R para propietario\n");
      if (S_ISDIR(atr.st_mode)) printf (" Es un directorio \n"); 
      if (S_ISREG(atr.st_mode))  
         /* ficheros modificados en los ultimos 10 dias */
	if ( (fecha - 10*24*60*60) <  atr.st_mtime) {
          printf ("FICHERO:%s: fecha acceso %s, en sgdos %d\n", rd1->d_name, 
			  ctime (&atr.st_mtime),(int) atr.st_mtime ); 
    	}
    } 
  } /* while*/
  closedir (d);
}
}/* main*/
