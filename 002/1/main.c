#include <stdio.h>
#include <string.h>


int main (int argc, char* argv[], char* env[])
{   
    int i;

    if (!env)
        return 1;
     
    for(i=0;env[i];i++)
    {
         if(strstr(env[i],"PWD="))
         {    
             printf("%s\n",env[i]);
             break; 
         }
     }
     return 0;
}
