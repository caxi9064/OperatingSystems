/* Este programa pide las notas de varios alumnos al usuario (3 notas por 
 * alumno) y despuÈs calcula la media */
//JosÈ Manuel PÈrez Lobato

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMALUMNOS 10
#define NUMNOTAS 3

struct Alumno {
  char nombre[20];
  float notas[NUMNOTAS]; };

typedef struct Alumno tAlumno;

void pedirNotas(tAlumno c[], int num);
void pedirNombres(tAlumno c[], int num);
float * calcularMedia(tAlumno c[], int num);
void mostrarMedia(float media[], int num);

int main () {
  tAlumno clase[NUMALUMNOS];
  float *media;
  int numAl;

  printf("Numero de alumnos (max 10) = "); 
  scanf("%d",&numAl); getchar();  
  printf("Numero de alumnos del grupo = %d\n", numAl); 

  pedirNombres (clase, numAl);
  pedirNotas (clase, numAl);
  media=calcularMedia (clase, numAl);
  mostrarMedia(media, numAl);
  
}
void pedirNombres(tAlumno c[], int num){
  int i,j;

  printf("\n");
  
  for (i=0;i<num; i++) {
      printf ("Dar el nombre del alumno %d:",i);
      fgets (c[i].nombre,20,stdin);
      c[i].nombre[strlen(c[i].nombre)-1]='\0';  //elimino el salto de lÌnea
    }
}
void pedirNotas(tAlumno c[], int num){
  int i,j;
  
  printf("\n");
  for (i=0;i<num; i++)
    for (j=0; j<NUMNOTAS;j++) {
      printf ("Dar la nota %d del alumno %s(decimales con .):",j,c[i].nombre );
      scanf ("%f", &(c[i].notas[j]) );
    }
}
float * calcularMedia(tAlumno c[], int num){
  int i,j;
  float suma,*media;
  
  media=(float *)malloc(NUMALUMNOS*sizeof(float));
  for (i=0;i<num; i++) {
    suma=0;
    for (j=0; j<NUMNOTAS;j++) 
      suma=suma+c[i].notas[j];
    media[i]=suma/NUMNOTAS;
  }  
  return media;
}
void mostrarMedia(float media[], int num){
  int i,j;
  
  printf("\n");
  for (i=0;i<num; i++)
    printf ("Nota media del alumno %d=%f\n",i,media[i]);
}

