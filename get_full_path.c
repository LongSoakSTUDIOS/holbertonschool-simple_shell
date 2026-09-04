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
 * get_full_path - function that fetches the path variable from the environment
 * and print to stderror if not found
 * @av: arguments sent when running our shell (Used to print program name)
 * @argv: tokenized arguments sent from user input within our shell
 * @buffer: one string of arguments sent from user input within our shell
 *
 * Return: returns the full path variable as a string, NULL if failed
 */
char *get_full_path(char **av, char **argv, char *buffer)
{
	char *full_path;

	full_path = _getenv("PATH");
	if (!full_path || *full_path == '\0')
	{
		fprintf(stderr, "%s: 1: %s: not found\n", av[0], argv[0]);
		free_all(buffer, argv, full_path, NULL);
		error_code = 127;
		return (NULL);
	}
	return (full_path);
}
