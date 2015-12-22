//summator  y=S(sin(dx))[dx=delta=N/n]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
//#include <iostream>
//using namespace std;
#define STACK_SIZE 10000
double S=0,N,delta; 
int    n,i;
 struct dS { double ni;
            double ni1;
            pid_t pid_clone;
          };

static int  thread_f(void* arg)
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
       
       struct dS* pdS= new struct dS[n];     
       pid_t pid;
       char *stack;
       char *stackTop;
       stack=(char*)malloc(STACK_SIZE *n);
       stackTop=stack;
       int status;
       
       delta=N/n;
       for (i=0; i<n; i++) 
       {          
           pdS[i].ni=i*delta;
           pdS[i].ni1=(i+1)*delta;
           stackTop=stackTop+STACK_SIZE;  
           pid = clone(thread_f,stackTop,CLONE_VM|SIGCHLD,&pdS[i]);
           if(pid==-1)
	   {
        	fprintf(stderr,"error: clone\n");
		return 1;
	   }
           pdS[i].pid_clone=pid;
       }      
       for(i=0; i<n; i++)
       {   
	  pid_t wpid=waitpid(pdS[i].pid_clone,&status,0); 

       }
       printf("N=%lf, n=%d,  y=S(sin(dx))[dx=delta=N/n]=%lf \n",N,n,S);
       delete [] pdS;
       return 0;
 }

