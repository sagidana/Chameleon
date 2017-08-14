#include "socks.h"


int open_socket_via_socks(uint8_t* proxy_host, uint8_t* proxy_port, uint8_t* remote_host, uint8_t* remote_port)
{
	struct sockaddr_in proxy = { 0 };
	struct sockaddr_in remote = { 0 };

	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > s) return -1;

	convert_to_sockaddr(proxy_host, proxy_port, &proxy);
	
	if (connect(s, (struct sockaddr *)&proxy, sizeof(proxy))) goto failure;

	if (!negotiate_with_proxy(s)) goto failure;

	convert_to_sockaddr(remote_host, remote_port, &remote);

	if (!send_connect_command(s, &remote)) goto failure;

	return s;
failure:
	close(s);
	return -1;
}

// Currently without any authentication.
bool negotiate_with_proxy(int s)
{
	uint8_t negotiate_request[3] = {0x5,  // SOCKS version.
									0x1,  // 
									0x0}; // No authentication.
	uint8_t reply[2] = { 0,0 };

	if (send(s, negotiate_request, sizeof(negotiate_request), 0) < 0) return false;

	if (recv(s, reply, sizeof(reply), 0) != 2) return false;

	if (reply[0] != 0x5 || 
		reply[1] != 0x0) 
		return false;

	return true;
}

bool send_connect_command(int s, struct sockaddr_in* remote)
{
	uint8_t reply[50] = { 0 };
	uint8_t connect_request[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int number_of_read_bytes = 0;

	connect_request[0] = 5; // SOCKS version.
	connect_request[1] = 1; // CMD -> CONNECT
	connect_request[2] = 0; // Reserved.
	connect_request[3] = 1; // Addr type -> IPv4
	memcpy(connect_request+4, &remote->sin_addr.s_addr, 4);
	memcpy(connect_request+8, &remote->sin_port, 2);

	if (send(s, connect_request, sizeof(connect_request), 0) < 0) return false;

	
	if ((number_of_read_bytes = recv(s, reply, sizeof(reply), 0)) <= 0) return false;	

	if (reply[0] != 0x5 || 
		reply[1] != 0x0) 
		return false;

	return true;
}

void convert_to_sockaddr(uint8_t* _host, uint8_t* _port, struct sockaddr_in* addr)
{
	uint16_t port = 0;
	sscanf((const char *)_port, "%hu", &port);

	addr->sin_family = AF_INET;
	addr->sin_port = htons(port);
	addr->sin_addr.s_addr = inet_addr((const char *)_host);
}