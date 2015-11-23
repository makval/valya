#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{   
    FILE *f1;
    char f_name[BUFSIZ],
         buf[BUFSIZ];        
    char *pbuf;
    int N=0;

    if(argc==3)
    {   
       if(!(f1=fopen(argv[2],"w")))
       {
          printf("error: user file: %s \n",argv[2]);           
          exit(1);
       }                
    }
    else
    {
        printf("error: arguments\n");
        exit(1);
    }
    pbuf=&buf[0];
    while(fgets(buf,BUFSIZ, stdin)!=NULL)  
    {  
       if(strstr(pbuf,argv[1]))
       {
          N++;
       } 
       fputs(buf,stdout);
    } 
    fprintf(f1,"\nThe string (%s) is found %d nambers.\n",argv[1],N);
  //  printf("\nThe string (%s) is found %d nambers.\n",argv[1],N);
    fclose(f1);
}
