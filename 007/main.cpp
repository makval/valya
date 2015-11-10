//summator  y=S(sin(dx))[dx=delta=N/n]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

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
       struct dS   *pdS;
       pthread_t*  pthread = new pthread_t[300];
     
       delta=N/n;
       for (i=0; i<n; i++) 
       {   
           pdS=(struct dS*)&dSi[i];
           dSi[i].ni=i*delta;
           dSi[i].ni1=(i+1)*delta;                
           if(pthread_create(&pthread[i],NULL,&thread_f,&pdS[i])!= 0)
	   {
        	fprintf(stderr,"error: pthread_create \n");
		return 1;
	   }
       }
       
       for(i=0; i<n; i++)
       {   
	   if(pthread_join(pthread[i],NULL) !=0)
    	   {
                fprintf(stderr,"error: pthread_join \n");
	   	return 1;
           }
       }
    
     printf("N=%lf, n=%d,  y=S(sin(dx))[dx=delta=N/n]=%lf \n",N,n,S);
     return 0;
 }

