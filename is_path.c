#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "main.h"

char *is_path(char **argv, char *buffer)
{
	char *valid_path;
		if (access(argv[0], X_OK) == 0)
		{
			valid_path = strdup(argv[0]);
			if (valid_path == NULL)
			{
				perror("Error");
				free_all(buffer, argv, NULL, NULL);
				return (NULL);
			}
		}
		else
		{
			perror("Error");
			free_all(buffer, argv, NULL, NULL);
			return (NULL);
		}
	return (valid_path);
}