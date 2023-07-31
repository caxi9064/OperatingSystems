#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  int pfds[2];
  char buf[30];
  
  pipe(pfds);
  
  if (!fork()) {
    close(pfds[0]);
    printf(" CHILD: sleeping 2 secs\n");
    sleep(2);
    printf(" CHILD: writing to the pipe\n");
    write(pfds[1], "test", 5);
    printf(" CHILD: exiting\n");
    exit(0);
  } else {
    close(pfds[1]);  
    printf("PARENT: reading from pipe\n");
    read(pfds[0], buf, 5);
    printf("PARENT: read \"%s\"\n", buf);
    wait(NULL);
  }
  return 0;
}
