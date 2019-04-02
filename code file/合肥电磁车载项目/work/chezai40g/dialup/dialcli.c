#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define DIALUP_SOCKET "/var/volatile/dialup.skt"


int main(int argc, char **argv)
{
	int ret;
	int sockfd;
	int addrlen;
	struct sockaddr_un addr;

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (-1 == sockfd) {
		perror("socket error()");
		exit(EXIT_FAILURE);
	}
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, DIALUP_SOCKET);
	addrlen = sizeof(addr);

	ret = connect(sockfd, (struct sockaddr *)&addr, addrlen);
	if (-1 == ret) {
		perror("connect() error");
		exit(EXIT_FAILURE);
	}
	write(sockfd, "PPPD", 4);

	close(sockfd);

	exit(EXIT_SUCCESS);
}

