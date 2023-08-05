#ifndef CORE
#define CORE
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
#include <signal.h>
#define PORT 9000
#define MAX_CLIENTS 10
#define MAX_BYTES 1024
#define END_SESSION "end"
#define FILE_CMD    "file"


typedef enum action_e
{
	GET,
	SET
} action_t;

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

/* Structure to (open/read/send/recv files). */
typedef struct File_t {
	char *name;
	char *chunk;
	FILE *fp; /* to write every chunk respectivly. */
} File_t;

void make_tcp_sock(int *fd);
void prepare_sock(socket_t *sock, int port);
void add_host(struct sockaddr_in *addr, char *host);
char *datetime();
int  sig_station(action_t a, int signal);
void handle_signal(int signal);
void signal_handler_init();

#endif /* CORE */
