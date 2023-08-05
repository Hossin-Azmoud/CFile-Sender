#include "file_receiver.h"
#define MAX_BYTES 1024

int main()
{
	int i;
	socket_t server = { 0 };
	time_t tick = time(NULL);
	buffer_t buff   = { 0 };
	int  connected = 0;
	buff.data       = NULL;

	make_tcp_sock(&(server.sockets.server_sk));
	prepare_sock(&server, PORT);
	add_host(&(server.server_addr), NULL);

	bind(
		server.sockets.server_sk, 
		(struct sockaddr*)(&(server.server_addr)), 
		sizeof((server.server_addr))
	);

	listen(server.sockets.server_sk, MAX_CLIENTS);
	printf("listening in port: %i\n", PORT);

	while (1)
	{
		server.sockets.client_sk = accept(server.sockets.server_sk, (struct sockaddr*)NULL, NULL);
		printf("client connected! \n");
		/* Client loop. */
		connected = 1;

		while (connected)
		{
			buff.data = malloc(sizeof(char) * MAX_BYTES);
			while ((buff.size = read(server.sockets.client_sk, buff.data, MAX_BYTES)) > 0)
			{
				buff.data[buff.size] = 0;
				
				for(i = 0; i < buff.size; i++)
					printf("%c -> %i\n", buff.data[i], buff.data[i]);
				if (strcmp(buff.data, "q") == 0)
				{
					printf("Disconnect msg!");
					connected = 0;
					break;
				}

				printf("CLIENT %s : %s\n", ctime(&tick), buff.data);
				free(buff.data);
				buff.data = malloc(sizeof(char) * MAX_BYTES);
			}
			if (buff.data != NULL)
				free(buff.data);
		}
		
		printf("A connection was lost!");
		close(server.sockets.client_sk);
		sleep(1);
	}

	return (0);
}
