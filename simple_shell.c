#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "main.h"

int main(int ac, char **av)
{
	char *buffer = NULL, *valid_path = NULL, *full_path = NULL;
	char **argv = NULL;
	int error_code = 0;

	(void)ac;
	signal(SIGINT, signal_handler);
	while (1)
	{
		buffer = NULL;
		argv = NULL;
		full_path = NULL;
		buffer = fill_buffer(&error_code);
		if (!buffer)
			continue;
		argv = tokenize(buffer, &error_code);
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
			full_path = get_full_path(av, argv, buffer, &error_code);
			if (!full_path)
				continue;
			valid_path = get_valid_path(av, argv, buffer, &error_code, full_path);
			if (!valid_path)
				continue;
		}
		spawn_child(argv, buffer, &error_code, full_path, valid_path);
	}
	return (0);
}
