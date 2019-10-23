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
	struct sockaddr_in servaddr, cliaddr;
	char recv_buffer[1024];
	int recv_len;
	socklen_t len;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		printf("socket() error: %s. \n", strerror(errno));
		return -1;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(32000);

	bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

	while (1)
	{
		len = sizeof(cliaddr);
		recv_len = recfrom(sockfd, recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr*) &cliaddr, &len);
		if (recv_len <= 0)
		{
			printf("recvfrom() error: %s \n", strerror(errno));
			return -1;
		}
		//TODO: check recv_buffer for proper header, more shit in assignment doc.
	}
	return 0;
}