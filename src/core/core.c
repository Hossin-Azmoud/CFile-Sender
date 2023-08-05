#include "core.h"

void make_tcp_sock(int *fd)
{
	*fd = socket(AF_INET, SOCK_STREAM, 0);

	if (*fd < 0)
	{
		printf("\n Error : Could not create socket \n");
		exit(1);
	}
}

void prepare_sock(socket_t *sock, int port)
{
	sock->server_addr.sin_family = AF_INET;
	sock->server_addr.sin_port   = htons(port);
}

void add_host(struct sockaddr_in *addr, char *host)
{
	if (host == NULL)
	{
		addr->sin_addr.s_addr = htonl(INADDR_ANY);
		return;
	}

	if (inet_pton(AF_INET, host, &(addr->sin_addr)) <= 0)
	{
		printf("\n The address might not be valid, inet_pton failed to convert it into IPV6\n");
		exit(1);
	}
}

char *datetime()
{
	time_t now = time(NULL);
	return ctime(&now);
}

int  sig_station(action_t a, int signal)
{
	static int internal_sig = 0;
	
	switch(a)
	{
		case GET: {
			return (internal_sig);
		} break;
		case SET: {
			internal_sig = signal;
			if (signal == SIGINT)
				printf("success capturing SIGINT\n");
		} break;
	}

	return (0);
}

void handle_signal(int signal)
{
	sig_station(SET, signal);
}

void signal_handler_init()
{
	struct sigaction sa;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
}
