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

	uint8_t reply[200] = { 0 };
	int number_of_read_bytes = 0;

	int s = open_socket_via_socks(proxy_host, proxy_port, remote_host, remote_port);

	if (s < 0) 
	{
		printf("error in create socks socket.\n");
		return -1;
	}


	unsigned char* get_request = "GET /index.html HTTP/1.1\r\n\r\n";
	if (send(s, get_request, strlen(get_request), 0) < 0)
	{
		printf("Error sending HTTP GET request: %s\n", strerror(errno));
		close(s);
		return -1;
	}	

	if ((number_of_read_bytes = recv(s, reply, sizeof(reply), 0)) <= 0)
	{
		printf("Error receiving reply: %s\n", strerror(errno));
		close(s);
		return -1;
	}		
	
	printf("Bytes received: ");
	printf("%.200s", reply);
	printf("\n");


	close(s);

	return 0;
}