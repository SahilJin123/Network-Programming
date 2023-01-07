#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<netdb.h>

void error(const char * msg)
{
 perror(msg);
 exit(1);
}

int main(int argc ,const char *argv[])
{

  int sockfd,portno,n;
  char buffer[1000];
  struct sockaddr_in serv_addr;
  
  struct hostent *server ;

  if(argc <3)
  {
   error("portno not passed ");
}  
   portno = atoi(argv[2]);
   sockfd = socket(AF_INET,SOCK_STREAM,0);
   if(sockfd <0)
  {
   error("portno not passed ");
}   

   server = gethostbyname(argv[1]);
     if(server== NULL)
  {
   error("No such Host");
}   

   bzero(&serv_addr , sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *) server->h_addr,(char*) &serv_addr.sin_addr.s_addr,server->h_length);
   serv_addr.sin_port = htons(portno);
   
   if(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0)
   {
     error("Error to  Connect");
    }
    
    while(1)
    {
        bzero(buffer,1000);
        fgets(buffer,1000,stdin);
        n = write(sockfd,buffer,strlen(buffer));
        if(n<0)
        {
            error("Error on writting");
        }
        
        bzero(buffer,1000);
        n = read(sockfd,buffer,1000);
        if(n<0)
        {
            error("Error on Reading");
        }
        printf("Server : %s\n",buffer);
        if(strncmp("exit",buffer,4)==0)
        break;
        
    }
    
    close(sockfd);
    
}
