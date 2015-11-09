// for func getenv(002)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void)
{   
    char* path; 
    
    path =getenv("PWD");
    if(path!=NULL)
        printf("Path: %s\n", path);
    return 0;     

}
