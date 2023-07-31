//Este programa crea el fichero que se utiliza en leerfichs.c
//José Manuel Pérez Lobato
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define TAMANO 100
int main () {
  int d;
  int i;
  int num=0;
  if ((d=open ("numeros.dat", O_CREAT|O_WRONLY,S_IWUSR|S_IRUSR))== -1) {
    printf ("Error en fichero\n");
    exit (0);
  }
  for (i=0; i<1000; i++) {
     if (i%100==0) num++;
     write (d, &num, sizeof(int)); 
  }
  close (d);
}
