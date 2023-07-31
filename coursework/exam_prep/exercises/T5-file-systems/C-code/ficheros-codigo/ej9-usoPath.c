/*
José Manuel Pérez Lobato
Uso sencillo de funciones de acceso al sistema de ficheros (mkdir, getcwd, chdir)
El programa muestra todos los directorios (rutas absolutas) que hay desde el directorio actual hasta el directorio raiz
*/
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(){
  char nombreDir [80];

  printf ("Creo un directorio\n");
  mkdir ("./DirNuevo", S_IWUSR|S_IRUSR);
  if (errno != 0 )
	  perror("Error creacion ./DirNuevo");
 
  strcpy (nombreDir,""); 
  getcwd(nombreDir,80);
  printf ("Nombre del directorio actual=%s\n", nombreDir);
  while ( strcmp(nombreDir,"/")!=0){
    chdir ("..");
    getcwd(nombreDir,80);
    printf ("Nombre del directorio actual=%s\n", nombreDir);
  }
}
