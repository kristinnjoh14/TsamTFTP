#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h> 

int main(int argc, char const *argv[])
{
	printf("%s\n", argv[1]);
	int testSocket = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in servaddr;
		
	char str[100];
	bzero( &servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(argv[1]);

	bind(testSocket, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(testSocket, 10);

	int comm_fd = accept(testSocket, (struct sockaddr*) NULL, NULL);

	while(1)
	{
		bzero( str, 100);

		read(comm_fd,str,100);

		printf("Echoing back - %d",comm_fd);

		write(comm_fd, str, strlen(str)+1);
	}

	return argc;
}