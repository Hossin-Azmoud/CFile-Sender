# CFile-Sender

A file sharing program using C

# Quick start
- the make file compiles everything, the client and the server for this application so u just need to:
```console
$ cd src
$ make && ./server # to run the server
$ make && ./client # to run the client
```
# DESC - NOTES

The server program will wait for a connection and when there is an active one, we try to capture a command...
commands that r supported for are:

(end):  ends the session.
    client/server tasks:
        1. free memory and end.

(file): in order for the client to send a file.
	
    client tasks:
        1. check if file exists.
        2. if not raise error, else open the file.
        3. send file name.
        4. send content.
		
    server tasks:
        1. recv file name.
        2. open file and store fp in file_t.
        3. recv chunks.

(exec): excute a command in the server. (experimental)
