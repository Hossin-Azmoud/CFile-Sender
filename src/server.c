#include "file_receiver.h"

#define MAX_CLIENTS 10

typedef struct server_socket_s
{
	int fd;
	int client_fd;
	struct sockaddr_in server_addr;
} socket_t;

int main()
{
	socket_t server = { 0 };
	char sendBuff[1025];
	time_t ticks;

	/* creates an UN-named socket inside the kernel and returns
	 * an integer known as socket descriptor
	 * This function takes domain/family as its first argument.
	 * For Internet family of IPv4 addresses we use AF_INET
	 */

	server.fd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&(server.server_addr), '0', sizeof(server.server_addr));
	memset(sendBuff, '0', sizeof(sendBuff));

	server.server_addr.sin_family = AF_INET;
	server.server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server.server_addr.sin_port = htons(PORT);

	bind(
		server.fd, 
		(struct sockaddr*)(&(server.server_addr)), 
		sizeof((server.server_addr))
	);


	listen(server.fd, MAX_CLIENTS);
	printf("listening in port: %i\n", PORT);

	while(1)
	{

		server.client_fd = accept(server.fd, (struct sockaddr*)NULL, NULL);
		ticks = time(NULL);
		snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
		write(server.client_fd, sendBuff, strlen(sendBuff));
		close(server.client_fd);
		sleep(1);

	}

	return (0);
}
