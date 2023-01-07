#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<netdb.h>  // define struct hostnet

void error(const char *msg)
{
  perror(msg);
  exit(1);
}
// int argc :- No. of parameters we our passing (Filename ,Port no) = 3
int main(int argc, char const* argv[])
{  
  int sockfd,portno,n;
  struct sockaddr_in serv_addr ; 
  
  char buffer[1000];
   if(argc <2)   //filename , serverip_address,portno
  {
    printf("Port number not provided\n");
    exit(1);
}

  portno = atoi(argv[1]);
  sockfd = socket(AF_INET,SOCK_STREAM,0);
   if(sockfd<0)
   {
      error("Error Opening Socket");
      
   }  
   
  // server = gethostbyname(argv[1]);
   //if(server == NULL)
   //{
     // fprintf(stderr ,"Error , No such Host");
    //}
     
     bzero((char *) &serv_addr ,sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     
     //bcopy((char *)server ->h_addr , (char *) &serv_addr.sin_addr.s_addr ,server->h_length);
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     
     if(connect(sockfd , (struct sockaddr *) &serv_addr ,sizeof(serv_addr)) <0) 
     error("Connection Failed");
     
     while(1)
  {
     bzero(buffer,1000);
    fgets(buffer,1000,stdin);
     n = write(sockfd , buffer ,strlen(buffer));
     if(n<0)
     {
        error("Error on Writting");
     
     }
     bzero(buffer,1000);
     n = read(sockfd,buffer,1000);

     if(n <0)
      error("Error On Reading ");
     
     printf("Server : %s\n",buffer);
     int i = strncmp("Bye",buffer ,3);
     if(i ==0)
     break;
  
  }

    close(sockfd);
    return 0;

}






