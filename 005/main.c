//shell1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

sig_atomic_t fl_sig=0;

void fl_handler(int sig)
{
    fl_sig = 1;
}


int main(void)
{
  char path[BUFSIZ],sh_com[BUFSIZ] ;
  struct sigaction act;
  act.sa_handler=fl_handler;
  sigaction(SIGINT, &act,0);
  path[0]=0;
  sprintf(path,"%s:%s",getenv("PATH"),getcwd(sh_com,BUFSIZ));
  setenv("PATH",path,1);
  printf("shell1 \n");
  
  while(1)
  {
    strcpy(sh_com,"");
    scanf("%s",sh_com);
    
    system(sh_com);

    if(fl_sig == 1)
    { 
      printf(" Goodbye \n"); 
      fl_sig=0;
      exit(0);
    } 
  }


  return 0; 
}


