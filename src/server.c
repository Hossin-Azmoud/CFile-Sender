#include "file_receiver.h"
/*
 DESC:
 - The server program will wait for a connection and when there is an active one, we try to capture a command...
 commands that r supported for are:
	- end:  ends the session. 
	- file: in order for the client to send a file.

		client tasks:
			1. check if file exists.
			2. if not raise error, else open the file.
			3. send file name.
			4. send content.
		
		server tasks:
			1. recv file name.
			2. open file and store fp in file_t.
			3. recv chunks.
	- exec: excute a command in the server. (experimental)
*/

void handle_client(int fd)
{
	buffer_t buff   = { 0 };
	int connected   = 1;
	buff.data       = NULL;

	while (connected)
	{
		buff.data = malloc(sizeof(char) * MAX_BYTES);
		buff.size = read(fd, buff.data, MAX_BYTES);
		
		while ((buff.size > 0) && connected)
		{
			buff.data[buff.size] = 0;

			if (strcmp(buff.data, END_SESSION) == 0)
			{
				free(buff.data);
				exit(0);
			}

			if (strcmp(buff.data) == FILE_CMD)
			{
				// TODO: make file protocol -> recv a file.
			}

			printf("\n%s(msg) -> %s\n", datetime(), buff.data);
			free(buff.data);
			buff.data = malloc(sizeof(char) * MAX_BYTES);
			buff.size = read(fd, buff.data, MAX_BYTES);
		}
		
		if (buff.data != NULL)
			free(buff.data);
	}

	printf("[INFO] client Disconnect at: %s\n", datetime());
	close(fd);
	return;
}

int main()
{
	socket_t server = { 0 };

	make_tcp_sock(&(server.sockets.server_sk));
	prepare_sock(&server, PORT);
	add_host(&(server.server_addr), NULL);
	// signal_handler_init();

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
		/* Handle client connection using the client sock fd */
		handle_client(server.sockets.client_sk);
		printf("A connection was lost!");
		close(server.sockets.client_sk);
		sleep(1);
	}

	return (0);
}
