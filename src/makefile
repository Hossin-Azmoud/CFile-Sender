CC=gcc
INCLUDE=-Ifile_sender -Ifile_receiver -Icore
CFLAGS=-Wall -pedantic -Werror -Wextra -std=c11

all: program

file_sender.o: file_sender/*.c file_sender/file_sender.h
	$(CC) $(CFLAGS) $(INCLUDE) -c file_sender/*.c

file_receiver.o: file_receiver/*.c file_receiver/file_receiver.h
	$(CC) $(CFLAGS) $(INCLUDE) -c file_receiver/*.c

program: main.c file_sender.o file_receiver.o
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

clean:
	rm *.o
	rm program
