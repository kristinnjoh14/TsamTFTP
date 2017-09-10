#include <sys/socket.h>
#include <sys/time.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>

//Gera #define ef gcc fer í f'ylu
static const int PACKET_SIZE = 512;

struct tftpPacket {
	unsigned short opcode;
	unsigned short packetno;
	char payload[508];
};

struct tftpRequest {
	int size;
	struct sockaddr_in client;
	struct tftpPacket packet;
};

int main(int argc, char const *argv[])
{
	if(argc < 3) {
		printf("Not enough arguments. Please give a port number and directory in that order :)\n");
		exit(0);
	}

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in servaddr, client;

	int portno = atoi(argv[1]);
	char directory[512];
	strcpy(directory, argv[2]);
	char payload[PACKET_SIZE-4];

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(portno);

	struct timeval timeout;
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

	bind(sockfd, (struct sockaddr *) &servaddr, (socklen_t) sizeof(servaddr));

	printf("Server listening on port %d\n", portno);
	while(1) {
		fd_set readies;
		FD_ZERO(&readies);
		FD_SET(sockfd, &readies);

		int ret = select(sockfd + 1, &readies, NULL, NULL, &timeout);

		if(ret == -1) {
			printf("Error beep boop\n");
			exit(-1);
		} else if(ret > 0) {
			struct tftpRequest *request;
			request = (struct tftpRequest *)malloc(sizeof(struct tftpRequest));
			bzero(request, sizeof(request));

			request->size = recvfrom(sockfd, &(request->packet), PACKET_SIZE,0,(struct sockaddr *)&(request->client), sizeof(struct sockaddr_in));
			request->packet.opcode = ntohs(request->packet.opcode);
			
			if(request->packet.opcode != RRQ)
		}
	}
}