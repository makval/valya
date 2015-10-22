//mykill
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

int pid,sig;

int main(int argc, char* argv[])
{
  if (argc!=3)
  {
    printf("Error input parameters\n");
    exit(1);
  }
  pid = atoi(argv[1]);
  sig = atoi(argv[2]);
  if(sig==SIGTERM)//kod=15       
  {
     if(kill(pid,sig) == -1)
     {
        printf("Error signal! \n");
        return 1;
     }
  }

  return 0; 
}

