#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int pfds[2];
  
  pipe(pfds);
  
  if (!fork()) {
    close(1);       /* close normal stdout */
    dup(pfds[1]);   /* make stdout same as pfds[1] */
    close(pfds[0]); 
    execlp("ls", "ls", NULL);
  } else {
    close(0);       /* close normal stdin */
    dup(pfds[0]);   /* make stdin same as pfds[0] */
    close(pfds[1]); 
    execlp("wc", "wc", "-l", NULL);
  }
  return 0;
}
