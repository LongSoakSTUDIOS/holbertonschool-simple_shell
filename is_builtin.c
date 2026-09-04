#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "main.h"

int is_builtin(char **argv, char *buffer)
{
	int i = 0;
	builtin_t builtins[] = {
		{"env" , print_env},
		{"setenv", _setenv},
		{NULL, NULL}
	};

	while (builtins[i].command != NULL)
	{
		if (strcmp(builtins[i].command, argv[0]) == 0)
		{
			error_code = 0;
			builtins[i].function(argv);
			free_all(buffer, argv, NULL, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}
