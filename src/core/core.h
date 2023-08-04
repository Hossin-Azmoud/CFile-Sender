#ifndef CORE
#define CORE
#define PORT 9000

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <assert.h>

typedef struct core_s
{
	char *name;
	int age;
} core_t;

core_t *create_new_core();
#endif /* CORE */
