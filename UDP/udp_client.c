#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	int ret;
	int sockfd;
	struct sockaddr_in servaddr;
	char send_buffer[1024];

	/*struct Datagram
	{
		char firstL[1];
		char lastL[1];
		int opcode[1];
		int length[1];
		char* message;
	};*/

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		printf("socket() error: %s. \n", strerror(errno));
		return -1;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(32000);


	while (1)
	{
		fgets(send_buffer, sizeof(send_buffer), stdin);
		//TODO: check user input for format

		ret = sendto(sockfd, send_buffer, sizeof(send_buffer), 0, (struct sockaddr *) &servaddr, sizeof(servaddr));

		if (ret <= 0)
		{
			printf("sendto() error: %s. \n", strerror(errno));
			return -1;
		}
		//TODO: add recvfrom() to get ack.
	}
	return 0;
}
