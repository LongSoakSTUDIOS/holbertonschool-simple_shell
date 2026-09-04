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
 * main - runs a simplified version of a shell
 * @ac: num of arguments
 * @av: array of the arguments
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	char *buffer = NULL, *valid_path = NULL, *full_path = NULL;
	char **argv = NULL;

	int argc = 0;
	int error_code = 0;
	int environ_is_heap = 0;

	(void)ac;
	signal(SIGINT, signal_handler);
	while (1)
	{
		buffer = NULL;
		argv = NULL;
		full_path = NULL;
		buffer = fill_buffer();
		if (!buffer)
			continue;
		argv = tokenize(buffer, av);
		if (!argv)
			continue;
		if (strchr(argv[0], '/') != NULL)
		{
			valid_path = is_path(argv, buffer);
			if (!valid_path)
				continue;
		}
		else
		{
			if (is_builtin(argv, buffer))
				continue;
			full_path = get_full_path(av, argv, buffer);
			if (!full_path)
				continue;
			valid_path = get_valid_path(av, argv, buffer, full_path);
			if (!valid_path)
				continue;
		}
		spawn_child(argv, buffer, full_path, valid_path);
	}
	return (0);
}
