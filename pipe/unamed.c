#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>    

int pip[2];
char buf [40];

int pere()
{
    write (pip[1],"hello, je suis le processus A",40);
    exit(0);
}

int fils()
{
  read (pip[0],buf,40);
  printf("%s", buf);
  exit(0);
}

int main (void)
{

  pipe(pip);
  int f;
  
  f = fork();
  
  printf("%d\n",f);

  switch(f)
  {
    case -1: perror("pipe");
             exit(1);
    case 0: fils();
    default: pere();         

  }

  return 0;

}
