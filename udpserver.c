#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>



int main(int argc, char **argv){
  int sockfd = socket(AF_INET,SOCK_DGRAM,0);

  struct timeval timeout;
  timeout.tv_sec=5;
  timeout.tv_usec=0;
  setsockopt(sockfd,SOL_SOCKET,
       SO_RCVTIMEO,&timeout,sizeof(timeout));
  
  struct sockaddr_in serveraddr,clientaddr;
  serveraddr.sin_family=AF_INET;

  //asking user for port number
  printf("Enter a port number: \n");
  char input[1000];
  fgets(input,1000,stdin);
  int port = atoi(input);

  serveraddr.sin_port=htons(port);
  serveraddr.sin_addr.s_addr=INADDR_ANY;

  bind(sockfd,(struct sockaddr*)&serveraddr,
       sizeof(serveraddr));


  while(1){
    int len = sizeof(clientaddr);
    char line[5000];
    int n = recvfrom(sockfd,line,5000,0,
         (struct sockaddr*)&clientaddr,&len);

    //the server recieved a message
    if(n!=-1){
      printf("Got from client: %s\n",line);
      //sending message back to client
      sendto(sockfd,line,strlen(line)+1,0,
               (struct sockaddr*)&clientaddr,sizeof(clientaddr));
    }
  }
}

