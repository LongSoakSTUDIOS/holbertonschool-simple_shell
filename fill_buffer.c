#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "main.h"

char *fill_buffer()
{
	int characters_read = 0;
	size_t size;
	char *buffer = NULL;
	
	if (isatty(0) == 1)
		printf("$");
	characters_read = getline(&buffer, &size, stdin);
	if (characters_read < 0)
	{
		free_all(buffer, NULL, NULL, NULL);
		if (characters_read == EOF)
		{
			exit(errno);
		}
		return (NULL);
	}
	if (buffer[characters_read - 1] == '\n')
		buffer[characters_read - 1] = '\0';
	return (buffer);
}