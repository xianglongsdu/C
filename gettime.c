#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	const int MAXLINE = 4096;
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2) 
		printf("usage: a.out <IPAddress>\n");

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
		printf("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		printf("inet_pton error for %s\n", argv[1]);

	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
			printf("connect error\n");
	
	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;
		if (fputs(recvline, stdout) == EOF)
			printf("fputs error\n");
	}

	if (n < 0) 
		printf("read error\n");

	exit(0);
}



