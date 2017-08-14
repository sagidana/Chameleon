#ifndef __SOCKS_H
#define __SOCKS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>


void convert_to_sockaddr(uint8_t* _host, uint8_t* _port, struct sockaddr_in* addr);
bool send_connect_command(int s, struct sockaddr_in* remote);
bool negotiate_with_proxy(int s);
int open_socket_via_socks(uint8_t* proxy_host, uint8_t* proxy_port, uint8_t* remote_host, uint8_t* remote_port);

#endif