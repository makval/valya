#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <dirent.h>

int main(int argc, char *argv[])
{
    int pid_user, n_pid;
    char name_dir[BUFSIZ];
    DIR *p_dir;
    struct dirent *pdrnt;

    if(argc==2)
    {
       pid_user=atoi(argv[1]);            
    }
    else
    {
        printf("error: arguments\n");
        exit(1);
    }
    sprintf(name_dir, "/proc/%d/task/", pid_user);
    p_dir=opendir(name_dir);
    pdrnt=readdir(p_dir);
    
    while(pdrnt!=NULL)
    {
       n_pid=atoi(pdrnt->d_name);
       if(n_pid>0)
       {         
         printf("-->%d \n",n_pid);        
       }    
       pdrnt=readdir(p_dir); 
    }
    closedir(p_dir);
    return 0;
}
   
