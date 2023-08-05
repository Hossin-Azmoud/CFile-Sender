#ifndef CORE
#define CORE
#define PORT 9000
#define _GNU_SOURCE

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <assert.h>

#define MAX_CLIENTS 10

typedef struct buffer_s
{
	char    *data;
	ssize_t size;
	size_t  cap;
} buffer_t;

typedef struct base_sock_s
{
	int server_sk;
	int client_sk;
} base_sock_t;

typedef struct server_socket_s
{
	base_sock_t sockets;
	struct sockaddr_in server_addr;
} socket_t;

void make_tcp_sock(int *fd);
void prepare_sock(socket_t *sock, int port);
void add_host(struct sockaddr_in *addr, char *host);

#endif /* CORE */
