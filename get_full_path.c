#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "main.h"

char *get_full_path(char **av, char **argv, char *buffer)
{
	char *full_path;
	
	full_path = _getenv("PATH");
	if (!full_path || *full_path == '\0')
	{
		fprintf(stderr, "%s: 1: %s: not found\n", av[0], argv[0]);
		free_all(buffer, argv, full_path, NULL);
		errno = 127;
		return (NULL);
	}
	return (full_path);
}
