#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<netinet/in.h>

void error(const char * msg)
{
  perror(msg);
  exit(1);
}

int main(int argc , char const* argv[])
{
 if(argc <1){
 error("Port No not Passed");
 }
 
 int sockfd,newsockfd,portno,n;
 char buffer[1000];
 struct sockaddr_in serv_addr,cli_addr ;
 socklen_t clilen ;
 sockfd = socket(AF_INET,SOCK_STREAM,0);
 if(sockfd <0){
 error("Error in creating Socket");
 } 
 
 bzero(&serv_addr , sizeof(serv_addr));
 portno = atoi(argv[1]);
 
 serv_addr.sin_family = AF_INET;
 serv_addr.sin_addr.s_addr = INADDR_ANY;
 serv_addr.sin_port = htons(portno);
 
 if(bind(sockfd ,(struct sockaddr*) &serv_addr,sizeof(serv_addr))<0)
 {
   error("Error On Binding");
 
 }
 
 listen(sockfd,5);
 clilen =sizeof(cli_addr);
 newsockfd = accept(sockfd,(struct sockaddr*) &cli_addr,&clilen);
  
  if(newsockfd <0){
 error("Error in Accpet");
 }
 
 while(1)
 {
   bzero(buffer,1000);
   n =read(newsockfd,buffer,1000);
   if(n <0){
   error("Error in Accpet");
    }
    
    n = write(newsockfd , buffer ,strlen(buffer));
     if(n <0)
     error("Error on Writting");
     
     int i = strncmp("Bye",buffer ,3);
     if(i ==0)
     break;
 
 
 }
 
close(newsockfd);
close(sockfd);


}
