#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define N 1


int main()
{
  int fd,n;
  char buf[N];
  
  /* Open an existing file read only */

  if ((fd=open("file_read",O_RDONLY,0666))<0) {
	perror("File does not exist\n");
	exit(1);
  }
  

  while ((n=read(fd,buf,N))>0)
    printf("Read from file character %c \n",buf[0]);
 
 if (n<0) {
    perror("Read error occured");
    return -1;
  }
  else 
    close(fd);
    return 0;
}
