#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int pid = fork();

  if (pid < 0)
  {
    fprintf(2, "fork error\n");
    exit(1);
  }

  if (pid == 0)
  {
    sleep(50);
    exit(1);
  }
  else
  {
    printf("Parent pid = %d, child pid = %d\n", getpid(), pid);
  
    if (argc == 1)
    {
      int status, cpid;
      cpid = wait(&status);

      printf("Child pid = %d exit with status %d\n", cpid, status);

      exit(0);
    }
    else 
    {
      char *option = "-o";
      if (argc > 2 || (strcmp(argv[1], option) != 0))
      {
        int status;
        wait(&status);

        fprintf(2, "Incorrect options\n");
      }
      else 
      {
        kill(pid);

        int status, cpid;
        cpid = wait(&status);

        printf("Child pid = %d exit with status %d\n", cpid, status);

        exit(0);
      }
    }
  }
  
  exit(0);
}
