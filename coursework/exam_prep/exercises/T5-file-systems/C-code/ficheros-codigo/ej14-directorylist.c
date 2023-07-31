#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/*This program receives a directory name and prints the names of the containing files and directories, their mode, their owner read right, their type (if they are or not directories), and, for the files modified within the last 10 days, their access time. 
*/

int main () {
int er;
char dirname[100], filename[100], resp[30];
struct stat atr;
DIR *d;
struct dirent *rd1;
time_t access_date;

printf (ÒDirectory name\n");
fgets (dirname, sizeof (dirname), stdin);
/* Delete \n from  the directory name*/
dirname[strlen(dirname)-1]='\0';

access_date=time(&access_date);
if ((d=opendir(dirname))==NULL) {
  printf ("This directory does not exist \n");
  return -1;
}
else {
  while (( rd1 =readdir(d)) != NULL) {
    if ( (strcmp(rd1->d_name, ".")!=0 )&& (strcmp(rd1->d_name, "..")!=0 )){
      strcpy (filename, dirname);
      strcat (filename, "/");
      strcat (filename, rd1->d_name);
      printf ("fichero :%s:", filename);
      er=stat (filename, &atr);
      printf ("modo :%#o:", atr.st_mode);
      if ((atr.st_mode & 0400) != 0) 
	 printf ("Read access for owner \n");
      else
	 printf (" No Read access for owner \n");
      if (S_ISDIR(atr.st_mode)) printf (" is a directory \n"); 
      if (S_ISREG(atr.st_mode))  
         /* files modifies withing the last 10 days */
	if ( (access_date - 10*24*60*60) <  atr.st_mtime) {
          printf ("FILE:%s: access date  %s, in seconds %d\n", rd1->d_name, 
			  ctime (&atr.st_mtime), atr.st_mtime ); 
    	}
    } 
  } /* while*/
  closedir (d);
}
}/* main*/

