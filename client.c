#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024

int main()
{
  char *ip = "192.168.56.103";
  int port = 8080;
  int e;
  char buffer[1024],book[1024];
  int sockfd, new_sock;
  struct sockaddr_in server_addr; 
  


  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
	printf("[+]Connected to Server.\n");
	
	bzero(buffer, 1024);
	recv(sockfd, buffer, sizeof(buffer), 0);
	printf("%s\n", buffer);
	
	scanf("%s",book);
	send(sockfd, book, sizeof(book),0);
	
	int n;
  FILE *fp;
  char *filename = "recv.txt";
  char data[SIZE];

  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, data, SIZE, 0);
    if (n <= 0){
      break;
    }
    fprintf(fp, "%s", data);
	if(buffer== 0){
		printf("[+]Data written in the file successfully.\n");
	}
    bzero(data, SIZE);
  }
    

  return 0;
}

