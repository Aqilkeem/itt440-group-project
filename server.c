#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define SIZE 1024

void send_file(FILE *fp, int client_sock){
  int n;
  char data[SIZE] = {0};

  while(fgets(data, SIZE, fp) != NULL) {
    if (send(client_sock, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}

     
int main(){
  char *ip = "192.168.56.103";
  int port = 8080;
  int e, bookname;
  char buffer[1024];
  char data[1024];
  int sockfd, client_sock,client_size;
  struct sockaddr_in server_addr,client_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("[-]Error in bind");
    exit(1);
  }
  printf("[+]Binding successfull.\n");

  if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		perror("[-]Error in listening");
    exit(1);
	}
	
	client_size = sizeof(client_addr);
	client_sock = accept(sockfd, (struct sockaddr*)&client_addr,&client_size);
	if (client_sock < 0){
        printf("Can't accept\n");
        return -1;
    }
    else printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	
	bzero(buffer, 1024);
    strcpy(buffer, "Welcome to server \nPlease enter the file title you want to search:\n");
    send(client_sock, buffer, strlen(buffer), 0);
	
	bzero(data,1024);
	bookname = recv(client_sock, data, sizeof(data),0);
	if ( bookname == -1 ) {
    printf ( "An error occured during the receive procedure \n" ) ;
    return 0 ;
  }
  else if( bookname > 0 ) {
	printf ("%s\n", data);
  }

  FILE *fp;
  char *filename = "send.txt";
  int n;
  char name[SIZE] = {0};
  
  
  if(strcmp(filename,data)== 1){
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(1);
  }
	
  while(fgets(name, SIZE, fp) != NULL) {
    if (send(client_sock, name, sizeof(name), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }else 
		printf("[+]File data sent successfully.\n");
    bzero(name, SIZE);
  }
  }
  

	
	
	
}

