#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>


void error(const char *msg)
{
  perror(msg);
  exit(1);
}
// int argc :- No. of parameters we our passing (Filename ,Port no) = 2
int main(int argc, char const* argv[])
{
  if(argc <2)
  {
    printf("Port number not provided\n");
    exit(1);
}
  int sockfd,portno, n;
  char buffer[1000];
  //sockaddr_in :- gives us internet address of server and client
  struct sockaddr_in serv_addr;
  //socklen_t is a 32 bit data type
   sockfd = socket(AF_INET,SOCK_DGRAM,0);
   if(sockfd<0)
   {
      error("Error Opening Socket");
      
   }  
   
   bzero((char *) &serv_addr ,sizeof(serv_addr));
   portno = atoi(argv[1]);
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
    
  
  if(bind(sockfd ,(struct sockaddr *) &serv_addr ,sizeof(serv_addr))<0)
  {
     error("Binding Failed");
   }
  
 
  while(1)
  {
     bzero(buffer,1000);
     n = read(sockfd,buffer,1000);
     if(n<0)
     {
        error("Error On Reading ");
     
     }
     printf("Client : %s\n",buffer);
     bzero(buffer,1000);
     fgets(buffer,1000,stdin);
     
     n = write(sockfd , buffer ,strlen(buffer));
     if(n <0)
     error("Error on Writting");
     
     int i = strncmp("Bye",buffer ,3);
     if(i ==0)
     break;
  
  }
  

close(sockfd);

}
