#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "main.h"
/**
 * fill_buffer - function that calls the getline function
 * and fills a buffer with the current command inputted into terminal.
 * The function calls exit when EOF signal is read
 *
 * Return: returns a filled buffer, NULL if failed
 */
char *fill_buffer(void)
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
			exit(error_code);
		}
		return (NULL);
	}
	if (buffer[characters_read - 1] == '\n')
		buffer[characters_read - 1] = '\0';
	return (buffer);
}
