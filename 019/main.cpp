#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <signal.h>

char *pCh1, *pCh2;
char  buf[BUFSIZ];  
int fCh1, fCh2; 
struct timeval term;
fd_set rfd1;
fd_set wfd2;

void handler_usr(int n)
{
   printf("Good-bye\n");
   close(fCh1);
   close(fCh2);
   if (raise(SIGTERM)==-1)
   {
      printf("error: SIGTERM\n");
   }
}
int main(int argc, char *argv[])
{   
     int nf1, nf2;
     struct sigaction act_usr;		
     sigemptyset(&act_usr.sa_mask);		
     act_usr.sa_handler=&handler_usr;	
     act_usr.sa_flags=0; 
              	
     if(sigaction(SIGINT,&act_usr,NULL)==-1)
     {
         printf("error: sigaction\n");
         exit(1); 
     }
     if(argc!=3)
     {        
        printf("error: arguments\n");
        exit(1);        
     }
     char *pCh1=argv[1];
     char *pCh2=argv[2];

     if(access(pCh1,F_OK))
     {
       nf1=mkfifo(pCh1,O_RDWR|S_IFIFO|S_IRWXU|S_IRWXG|S_IRWXO);// 0777);
       if(nf1==-1)
       {
          printf("error create Fifo1\n");//read
          exit(1);    
       }
    }   
    if(access(pCh2,F_OK)==-1)
    {
	nf2=mkfifo(pCh2,O_RDWR|S_IFIFO|S_IRWXU|S_IRWXG|S_IRWXO);// 0777);
        if(nf2==-1)
        {
           printf("error create Fifo2\n");
           exit(1);    
        }
    }
    fCh1=open(pCh1,O_RDWR);
    if(fCh1<0)
    {
           printf("error open Ch1\n");
           exit(1);    
    }
    fCh2=open(pCh2,O_RDWR);
    if(fCh2<0)
    {
           printf("error open Ch2\n");
           exit(1);    
    }
    while(1)
    { 
        FD_ZERO(&rfd1);			
	FD_SET(STDIN_FILENO,&rfd1);
	FD_SET(fCh1,&rfd1);
        term.tv_sec=15;
        term.tv_usec=0;
	int ready=select(10,&rfd1,NULL,NULL,&term);
        if(ready)
        {
             if(FD_ISSET(STDIN_FILENO,&rfd1))
             {
                if(fgets(buf,BUFSIZ,stdin)!= 0)
                {
                     int rez=write(fCh2,buf,BUFSIZ);
                     if(rez==-1)
                     {
                        printf("error open Ch2\n");
                        exit(1); 
                     } 
                 }
              } 
              if(FD_ISSET(fCh1,&rfd1))
              {
		int rez_in=read(fCh1,buf,BUFSIZ);
		if(rez_in==-1)
                {
                        printf("error open Ch1\n");
                        exit(1); 
                 } 					
		 printf("%s\n",buf);
              }
          }
     }      
     return 0;
}  
