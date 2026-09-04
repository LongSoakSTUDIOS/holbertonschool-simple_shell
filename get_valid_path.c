#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "main.h"

char *get_valid_path(char **av, char **argv, char *buffer, char *fp)
{
	char *valid_path;

	valid_path = find_exec(fp, argv[0]);
	if (!valid_path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", av[0], argv[0]);
		free_all(buffer, argv, fp, NULL);
		error_code = 127;
		return (NULL);
	}
	return (valid_path);
}
