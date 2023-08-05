#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *buff   = NULL;
	size_t cap   = 0;
	ssize_t size = 0;
	
	if ((size = getline(&buff, &cap, stdin)) != EOF)
		printf("buff: \ncontent: %s \ncap: %li\nsize: %li\n", buff, cap, size);

	free(buff);
}
