#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
    FILE *f1;
    char buf[BUFSIZ],
         com_user[BUFSIZ];
    char *pcom;
    int N,i;

    if(argc==2)
    {   
       pcom=&com_user[0];
       for(i=1;i<argc;i++)
       {
            pcom=strcat(com_user,argv[i]);
            pcom=strcat(com_user," ");
       }                 
    }
    else
    {
        printf("error: arguments\n");
        exit(1);
    }
    if(!(f1=popen(com_user,"r")))
    {
        exit(1);
    }
    while(fgets(buf, sizeof(buf), f1)!=NULL)  
    { 
       N=strlen(buf);
       for(i=0;i<N/2;i++)
       {
          char p;
          p = buf[i];
          buf[i]=buf[N-i-1];
          buf[N-i-1]=p;
       }
       printf("%s",buf);
    } 
    printf("\n");
    pclose(f1);
}
