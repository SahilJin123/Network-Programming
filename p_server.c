#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
//#include<netdb>

void error(const char *msg)
{
  perror(msg);
  exit(1);
 }

int main(int argc , char const* argv[])
{
   
   int sockfd,newsockfd,portno,n;
   char buffer[1000];
   struct sockaddr_in serv_addr ,cli_addr; 
   socklen_t clilen;
   sockfd = socket(AF_INET,SOCK_STREAM,0);
   if(sockfd <0)
   {
       error("Socket Creation Error");
   }
   
   
   bzero(&serv_addr,sizeof(serv_addr));
   portno = atoi(argv[1]);
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY ;
   serv_addr.sin_port = htons(portno);
   
   if(bind(sockfd ,(struct sockaddr*) &serv_addr , sizeof(serv_addr))<0)
   {
         error("Binding Error");
   }
   
   listen(sockfd ,5);
   clilen= sizeof(cli_addr);
   newsockfd =  accept(sockfd ,(struct sockaddr*)  &cli_addr,&clilen);
   
   if(newsockfd<0)
   {
      error("Error on accept");
   }
   
   while(1)
   {
      bzero(buffer,1000);
      n = read(newsockfd , buffer,1000);
      if(n<0)
     {
      error("Error on Reading");
     }
     bzero(buffer,1000);
     fgets(buffer,1000,stdin);
     
     n = write(newsockfd,buffer,strlen(buffer));
     if(n<0)
     {
      error("Error on Writing");
     }


   }

close(newsockfd);
close(sockfd);   
   
}



