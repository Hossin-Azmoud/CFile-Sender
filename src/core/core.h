#ifndef CORE
#define CORE
#define PORT 9000
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
typedef struct core_s
{
	char *name;
	int age;
} core_t;

core_t *create_new_core();
#endif /* CORE */
