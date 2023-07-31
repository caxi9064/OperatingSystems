/*
 * Programa que recibe un numero como parametro y muestra en pantalla  un mensaje con el n˙mero recibido, junto con su pid
 * 	gcc -o hijo hijo.c
//JosÈ Manuel PÈrez Lobato
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
 int pid;
 int cont=0;

   pid=getpid();
   printf("Soy hijo %s con Pid: %d  \n",argv[1],pid);
   sleep(2);
}
