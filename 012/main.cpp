#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <pthread.h>
#include <signal.h>
#include <vector>

using namespace std;

int nRd,nWr,zRdWr;
vector <int> vectorWR;
pthread_mutex_t mutex;
sig_atomic_t sig_flag=0;	

void *thread_Wrfunc(void *zRdWr)
{ 
  while(!sig_flag)
  {
     long int size = vectorWR.size();
     pthread_mutex_lock(&mutex);
     if(vectorWR.size()<*(int*)zRdWr)
     {
        vectorWR.insert(vectorWR.end(),1);
     }
     pthread_mutex_unlock(&mutex);     
   }
   return 0;
}
void *thread_Rdfunc(void *zRdWr)
{ 
  while(!sig_flag)
  {
     
     pthread_mutex_lock(&mutex);
     if(vectorWR.size()>0)
     {
        vectorWR.erase(vectorWR.begin());
     }
     pthread_mutex_unlock(&mutex);     
   }
   return 0;
}
int main(int argc, char *argv[])
{   
    int i;
    if(argc!=3)
    {        
      printf("error: arguments\n");
      exit(1);        
    }
   
    nRd=atoi(argv[1]); 
    nWr=atoi(argv[2]);
    zRdWr=atoi(argv[3]);//max
    if((zRdWr>10000)||(nRd>100)||(nWr>100))
    {        
      printf("error: arguments\n");
      exit(1);        
    }
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT, &act, NULL);
    pthread_t *thread_Wr=new pthread_t[nWr];
    pthread_t *thread_Rd=new pthread_t[nRd];
    
    for(i=0;i<nWr;i++)
    {
       if(pthread_create(&thread_Wr[i],NULL,&thread_Wrfunc,&zRdWr))
       {        
          printf("error: pthread_create Wr\n");
          return 1;        
       }
    }
    for(i=0;i<nRd;i++)
    {
       if(pthread_create(&thread_Rd[i],NULL,&thread_Rdfunc,&zRdWr))
       {        
         
          return printf("error: pthread_create Rd\n"); 1;        
       }
    }
    for(i=0;i<nWr;i++)
    {
	if(pthread_join(thread_Wr[i],NULL)!=0)
        {
           fprintf(stderr,"ERROR: join thread_Wr\n");
	   return 1;
	}
    }
    for(i=0;i<nRd;i++)
    {
         if(pthread_join(thread_Rd[i],NULL)!=0)
         {
             fprintf(stderr,"ERROR: join thread_reader \n");
             return 1;
          }
    }
    while(1)
    {
         if(sig_flag==1)
         {
            printf("Good-bye!\n");
            return 1; 
         } 
    }

    pthread_mutex_destroy(&mutex);
    delete [] thread_Rd;
    delete [] thread_Wr;
    
    return 0;

   
}  
