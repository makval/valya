//summator y=sin(x)[0 ...N]
#include <stdio.h>
#include <stdlib.h>
#include <string.h
#include <malloc.h>
#include <pthread.h>
#include <unistd.h>

double S=0,N,delta; 
int    n,i;
struct dS { double ni;
            double ni1;
          };

void* thread_f(void* arg)
{      
    struct dS* pSi=(struct dS*) arg;   
    S+=(fabs(sin(pSi->ni))+fabs(sin(pSi->ni1)))/2;
    return 0;
}   

int main(int argc, char *argv[])
{
    if(argc==3)
    {
        N = atof(argv[1]);
        n = atoi(argv[2]);       
    }
    else
    {
        printf("error: arguments\n");
        exit(1);
    }
    if((n>300)||(n<=0))
    {
       printf("error: n\n");
       exit(1);
    } 
 
       struct dS   dSi[300];
       struct dS *pdS;
       pthread_t*  thread;
       pthread_t*  pthread[300];
     
       delta=N/n;
       for (i=0; i<n; i++) 
       {   thread=pthread[i];
           pdS=(struct dS*)&dSi[i];
           dSi[i].ni=i;
           dSi[i].ni1=i+delta;                
           if(pthread_create(thread,NULL,&thread_f,&pdS[i])!= 0)
	   {
        	fprintf(stderr,"error: pthread_create \n");
		return 1;
	   }
       }
       for(i=0; i<n; i++)
       {   
           thread=pthread[i];
	   if(pthread_join(thread,NULL) !=0)
    	   {
                fprintf(stderr,"error: join \n");
	   	return 1;
           }
       }    
     printf("N=%lf, n=%d, y=sin(x)=%lf \n",N,n,S);
     return 0;
 }

         

