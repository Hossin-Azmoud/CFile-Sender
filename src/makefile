CC=gcc
INCLUDE=-Ifile_sender -Ifile_receiver -Icore
CFLAGS=-Wall -pedantic -Werror -Wextra -std=c11

all: client server

file_sender.o: file_sender/*.c file_sender/file_sender.h core/*.c core/*.h
	$(CC) $(CFLAGS) $(INCLUDE) -c file_sender/*.c core/*.c

file_receiver.o: file_receiver/*.c file_receiver/file_receiver.h core/*.c core/*.h
	$(CC) $(CFLAGS) $(INCLUDE) -c file_receiver/*.c core/*.c

client: client.c file_sender.o core.o
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

server: server.c file_receiver.o core.o
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

clean:
	rm *.o server client
