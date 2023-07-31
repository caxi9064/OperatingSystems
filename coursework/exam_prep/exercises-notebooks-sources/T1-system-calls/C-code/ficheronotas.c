/* Este programa pide las notas de varios alumnos al usuario (3 notas por 
 * alumno) y despuÈs calcula la media */
//JosÈ Manuel PÈrez Lobato

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define NUMALUMNOS 10
#define NUMNOTAS 3

struct Alumno {
  char nombre[20];
  float notas[NUMNOTAS]; };

typedef struct Alumno tAlumno;

void pedirAlumno(tAlumno *alumno);
void escribirAlumno(tAlumno alumno, int fd);

int main (int argc, char **argv) {
  tAlumno clase[NUMALUMNOS];
  tAlumno Al;
  float *media;
  int i, numAl, fichid;

  printf("Numero de alumnos (max 10) = "); 
  scanf("%d",&numAl); getchar();  
  printf("Numero de alumnos del grupo = %d\n", numAl); 

  fichid = open(argv[1], O_RDWR|O_CREAT, 0660); 

  for (i=0; i< numAl; i++) {
     pedirAlumno (&Al);
     escribirAlumno (Al, fichid);
  }

  close(fichid);
  
}
void pedirAlumno(tAlumno *alumno){
  int j;

   printf ("Nombre del alumno: ");
   fgets (alumno->nombre,20,stdin);
   alumno->nombre[strlen(alumno->nombre)-1]='\0';  //elimino el salto de lÌnea
   getchar();
  
   printf("\n");
   for (j=0; j<NUMNOTAS;j++) {
      printf ("Dar la nota %d del alumno %s(decimales con .):",j,alumno->nombre );
      scanf ("%f", &(alumno->notas[j]) ); getchar();
    }
}


void escribirAlumno(tAlumno alumno, int fd){
  char linea[80];

  sprintf (linea, "%s %4.2f %4.2f %4.2f \n", alumno.nombre, alumno.notas[0], alumno.notas[1], alumno.notas[2]);
  write (fd, linea, strlen(linea)) ;

}

