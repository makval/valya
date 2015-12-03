#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <syslog.h>

 int flag_usr1=0;
 int flag_usr2=0;  

void sig_handler1(int s)
{
                flag_usr1++;
		openlog("stat_server", 0, LOG_USER);
		syslog(LOG_NOTICE, "Daemont 1- %d", flag_usr1);
		closelog();
		

}
void sig_handler2(int s)
{
	
		flag_usr2++;
                openlog("stat_server", 0, LOG_USER);
		syslog(LOG_NOTICE, "Daemont 2 -%d",flag_usr2);
		closelog();
		

}


int main(int argc,char* argv[])
{
            
       syslog(LOG_NOTICE, "Parent is starting");
       printf("start\n");  
       pid_t pid = fork();     //создаем потомка
       if(pid == -1)
       {  //если не удалось запустить потомка	
	    printf("Error: start Daemon failed\n");
	    exit (1);
       }
       else if(pid == 0)
            {     //если это потомок
	        setsid();       //создаем новый сеанс
	        chdir("/");     //идем в корень
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
			
		syslog(LOG_NOTICE, "Daemont starting");

                sleep(1);
        //sig_us1
                struct sigaction sig_usr1;
                sigemptyset(&sig_usr1.sa_mask);
                sig_usr1.sa_flags=0;
                sig_usr1.sa_handler=sig_handler1;
                if(sigaction(SIGUSR1,&sig_usr1,NULL)==-1)
                {
                     printf("\nError sigaction  sig 1");
                     return 1; 
               }

        //sig_us2
                struct sigaction sig_usr2;
                sigemptyset(&sig_usr2.sa_mask);
                sig_usr2.sa_flags=0;
                sig_usr2.sa_handler=sig_handler2;
                if(sigaction(SIGUSR2,&sig_usr2,NULL)==-1)
                {
                    printf("\nError sigaction  sig 2");
                    return 1; 
                }


                char message[BUFSIZ];	
		int sock = socket(AF_INET,SOCK_STREAM,0);
		if(sock == -1)
		{
			fprintf(stderr,"ERROR: create socket() \n");
			exit(1);
		}
        	
		struct sockaddr_in serv_addr;
		int my_port = htons(8888);	//port
		memset(&serv_addr, 0, sizeof(sockaddr_in));		
		// параметры соединения
		serv_addr.sin_family = AF_INET;	//internet
		serv_addr.sin_port = htons(my_port);		//порт
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		
		if(bind(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
		{
			close(sock);
			exit(1);
		}
		listen(sock,5);		//очередь 
		int name_client = 0;	//имя клиента 


               while(1)
	       {	
		  int sock_accept = accept(sock,NULL,NULL);	//новый сокет 
		  if(sock_accept < 0)
		  {
			printf("accept () \n");
		  }
		  while(1)
		  {//ожидаем сообщение
			  int bytes = recv(sock_accept,message,sizeof(message),0);
			  if(bytes<=0)
					break;
			   syslog(LOG_NOTICE, "message %s",message);
		}
	    }
    }
    else  printf(" BAY");
   // sleep(1); 

return 0; 
}

