
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main()
{
  int pfds[2];
  char buf[30];
  
  if (pipe(pfds) == -1) {
    perror("pipe");
    exit(1);
  }
  
  printf("writing to file descriptor #%d\n", pfds[1]);

  if (write(pfds[1], "test", 5)<0){
    perror("write");
    exit(1);
  }
  printf("reading from file descriptor #%d\n", pfds[0]);

  if (read(pfds[0], buf, 5)<0){
    perror("write");
    exit(1);
  }
  printf("read \"%s\"\n", buf);

  return 0;
}

