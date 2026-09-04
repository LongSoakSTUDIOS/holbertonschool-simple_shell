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
 * get_valid_path - function that checks if a path is valid, and prints
 * an error if not
 * @av: arguments sent when running our shell (Used to print program name)
 * @argv: tokenized arguments sent from user input within our shell
 * @buffer: one string of arguments sent from user input within our shell
 * @fp: full_path to check
 *
 * Return: returns a valid path to an executable, NULL if failed to find one
 */
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
