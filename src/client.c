#include "file_sender.h"

int main(int argc, char *argv[])
{
	socket_t client = { 0 };
	buffer_t buff   = { 0 };
	buff.data       = NULL;

	if(argc != 2)
	{
		printf("\n Usage: %s <ip of server> \n",argv[0]);
		return 1;
	}

	make_tcp_sock(&(client.sockets.server_sk));
	prepare_sock(&client, PORT);
	add_host(&(client.server_addr), argv[1]);

	if(connect(client.sockets.server_sk, (struct sockaddr *)&(client.server_addr), sizeof(client.server_addr)) < 0)
	{
		printf("\n Error : Connect Failed \n");
		return 1;
	}

	while (1)
	{
		printf("$ ");
		buff.size = getline(&buff.data, &buff.cap, stdin);
		buff.data[buff.size - 1] = 0;
		/* Send data using the server sock fd. */
		write(client.sockets.server_sk, buff.data, (buff.size - 1));
		if (strcmp(buff.data, END_SESSION) == 0)
		{
			break;
		}

		if (buff.data != NULL)
		{
			free(buff.data);
			buff.data = NULL;
		}
	}

	if (buff.data != NULL)
		free(buff.data);

	return 0;
}
