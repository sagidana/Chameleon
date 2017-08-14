#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#include "socks.h"

int main(int argc, char **argv)
{
	if (argc != 5)
	{
		printf("Usage: bot <proxy_host> <proxy_port> <remote_host> <remote_port>\n");
		return -1;
	}

	uint8_t *proxy_host = argv[1];
	uint8_t *proxy_port = argv[2];
	uint8_t *remote_host = argv[3];
	uint8_t *remote_port = argv[4];

	uint8_t payload[200] = { 0 };
	int number_of_read_bytes = 0;
	int s;

	// /* 
	// 	-------- Using SOCKS -------- 
	// */
	// s = open_socket_via_socks(proxy_host, proxy_port, remote_host, remote_port);
	// if (s < 0) 
	// {
	// 	printf("error in create socks socket.\n");
	// 	return -1;
	// }

	struct sockaddr_in remote = { 0 };

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > s) return -1;

	convert_to_sockaddr(remote_host, remote_port, &remote);
	
	if (connect(s, (struct sockaddr *)&remote, sizeof(remote))) return -1;

	if ((number_of_read_bytes = recv(s, payload, sizeof(payload), 0)) < 0) return -1;

	printf("%d", number_of_read_bytes);


	close(s);

	return 0;
}