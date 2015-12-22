#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
//#include <sys/wait.h>
#include <pthread.h>



char *pCh1, *pCh2;
char  buf1[BUFSIZ],buf2[BUFSIZ];  
int fCh1, fCh2; 
void* Ch2i(void *n2)
{  
   int wr2;
   while(1)
   { 
      if(scanf("%s",buf2)>0)
      { 
         fCh2=open(pCh2,O_RDWR);
         if(fCh2==-1)
         {
             printf("error open\n");
         } 
         wr2= write(fCh2,buf2,strlen(buf2));
         if(wr2==-1)
         {
             printf("error write\n");
             pthread_exit(NULL);
         } 

         printf("  %s\n",buf1);
         close(fCh1); 
      }
   }
}

int main(int argc, char *argv[])
{   
    int nf1, nf2, n1,n2; 
     pthread_t  P2; 

    if(argc!=3)
    {        
      printf("error: arguments\n");
      exit(1);        
    }
    pCh1=argv[1];
    pCh2=argv[2];

    if(access(pCh1,F_OK)==-1)
    {
       nf1=mkfifo(pCh1,O_RDWR|S_IFIFO|S_IRWXU|S_IRWXG|S_IRWXO);// 0777);
       if(nf1==-1)
       {
          printf("error create Fifo1\n");
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
    if(pthread_create (&P2,NULL,Ch2i,pCh2)!=0)
    {
           printf("error create pthread\n");
           exit(1); 
    } 
    while(1)
    { 
           fCh1=open(pCh1,O_RDWR);
           if(fCh1==-1)
           {
                printf("error open Fifo1\n");
           }
           read(fCh1,buf1,BUFSIZ);
           printf("%s\n",buf1);
           close(fCh1); 
        
     }  
    
   
    pthread_join(P2,NULL);
    return 0;



}  
