#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int c, char **v, char **env)
{
   printf(" %d %p %p \n",c,v,env);

//print pwd (func getenv)
   if(*env)
   {
     char *c_dir = getenv ("PWD");
     printf("CURRENT PATH of getevn functions: %s \n",c_dir);
   }

// print pwd
   while(*env)
   {
     char *p = strstr(*env,"PWD=");
     if(p==*env)
     printf("CURRENT PATH of main functions: %s \n",(p+4));
     env++;
   }
  return 0;
}
