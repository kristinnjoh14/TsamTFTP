#include <sys/socket.h>
#include <sys/time.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h> 

int main(int argc, char const *argv[])
{
	int packetSize = 512;
	int socket = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in servaddr;

	int portno = argv[1];
	char directory[512];
	strcpy(directory, argv[2]);

	printf("%s %s", portno, directory);

	char msg[packetSize];
	bzero( &servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(portno);

	struct timeval timeout;
	timeout.tv_sec = 30;
	timeout.tv_usec = 0;
	setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

	bind(socket, (struct sockaddr *) &servaddr, (socklen_t) sizeof(servaddr));



	return argc;
}