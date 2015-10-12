#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

int parent_pid(int pid_code)
{
  FILE *f1;
  char name_dir[BUFSIZ];  //имя файла с путем
  char str1[20];
  char buf_ppid[10];		//для PID 10 символов
  int  num_ppid =0;

  sprintf(name_dir,"/proc/%d/status",pid_code);  
  f1 = fopen(name_dir,"r");
  if(!f1)
  {
     printf("ERROR! can`t open file \n");
     exit (1);
  }
  while (fgets(str1,sizeof(str1),f1))
  {
      if (strstr(str1,"PPid"))   //нашел прародителя
      { 
         strcpy(buf_ppid,&str1[6]);
         num_ppid = atoi(buf_ppid);
         //printf("НАШЕЛ!!!!!!!!!!!! ppid = %d \n", num_ppid);
         break;
      }	
  } 
  fclose(f1);
  return num_ppid;
}

//функция формирования дерева родителей процесса
int print_tree(int pid_code)
{
  char tree_pid[BUFSIZ];  //дерево процесса
  char buf[10];           //вспомогательный буфер
  int  ppid_code = 0;     //родитель

  sprintf(tree_pid,"%d",pid_code);
  while(pid_code)
  {
      ppid_code = parent_pid(pid_code);   //получаем родителя
      sprintf(buf," --> %d",ppid_code);
      strcat(tree_pid,buf);
      pid_code = ppid_code;
      if(!ppid_code) //нашли родителя 0
           printf(" * %s \n",tree_pid);
   }
   return 0;
}

// чтение всех процессов дирректории ./proc
int dir_proc()
{
    DIR *dir;
    struct dirent *entry;
    dir = opendir("/proc/");    
    if(!dir) 
    {
        perror("diropen");
        exit(1);
    };
    while((entry = readdir(dir))!= NULL)
    {
        if (atoi(entry->d_name))
            print_tree(atoi(entry->d_name));
    };
    closedir(dir);
    return 0;
}
//----------------------------------------
int main(int arg,char **argv)	
{				
  if(arg == 1)        
      dir_proc();    
  else 
      if (arg == 2)   
           print_tree(atoi(argv[1]));
      else
           printf("ERROR:  %d !\n",arg);
  return 0;
} 
