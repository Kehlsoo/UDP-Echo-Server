#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char** argv){
  int sockfd = socket(AF_INET,SOCK_DGRAM,0);
  if(sockfd < 0){
    printf("There was an error creating the socket\n");
    return 1;
  }

  struct sockaddr_in serveraddr;
  serveraddr.sin_family=AF_INET;

  //asking user for port number
  printf("Enter a port number: \n");
  char input[5000];
  fgets(input,5000,stdin);
  int port = atoi(input);

  serveraddr.sin_port=htons(port);

  //asking user an IP address
  printf("Enter an IP address: \n");
  char ip[5000];
  fgets(ip,1000,stdin);

  serveraddr.sin_addr.s_addr=inet_addr(ip);

  //asking for message
  printf("Enter a message: ");
  char line[5000];
  fgets(line,5000,stdin);

  //sending message
  sendto(sockfd,line,strlen(line)+1,0,
   (struct sockaddr*)&serveraddr,sizeof(serveraddr));

  char message[5000];
  int len = sizeof(serveraddr);

    //recieving message
  recvfrom(sockfd,message,5000,0,(struct sockaddr*)&serveraddr,&len);

  printf("Message recieved from server: %s\n",message);
  close(sockfd);
  return 0;
  
}