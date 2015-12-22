#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<fcntl.h>
#include <netinet/in.h>

int port1,port2,socksrv;

void *thread_func(void *arg)
{
    char buf[BUFSIZ];
    struct sockaddr_in addr;
    int s;

    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port1); 
    addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
    
    while(1)
    {
       if(scanf("%s",buf)>0)
       {
	  if(s=sendto(socksrv,buf,strlen(buf),0,(struct sockaddr*)&addr,sizeof(addr))<0)
          {
             printf("Error calling sendto()\n");
             exit(1);        				
          }
       }
    }
}


int main(int argc, char *argv[])
{   
   
    char buf[BUFSIZ];
    struct sockaddr_in addr;
    int s,r;
    pthread_t thread;

    if(argc!=3)
    {        
      printf("error: arguments\n");
      exit(1);        
    }
    port1=atoi(argv[1]);
    port2=atoi(argv[2]);
    if(( s=socket(AF_INET,SOCK_DGRAM,0))<0)
   // if(s<0) 
    {
      printf("Error calling socet()\n");
      exit(1);        
    }   
    memset(&addr, 0, sizeof(sockaddr_in));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port1); 
    addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
    if(bind(s,(struct sockaddr*)&addr,sizeof(addr))< 0)
    {
       printf("Error calling bind()\n");
       exit(1);        
    }    
    if(pthread_create(&thread,NULL,&thread_func,NULL)!=0)
    {
       printf("Error pthread_create()\n");
       exit(1); 
    }    
    while(1)
    {
       memset(&buf,0,sizeof(buf));
       if(r=recvfrom(s,buf,BUFSIZ,0,NULL,NULL)<0)
       {
          printf("Error reconfrom()\n");
          close(s); 
          printf("%s\n",buf);
          exit(1); 
       }
    }
    return 0;
}
           




