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
 * is_builtin - function that checks if a command is a built in shell function
 * and runs the function if found
 * @argv: tokenized arguments sent from user input within our shell
 * @buffer: one string of arguments sent from user input within our shell
 *
 * Return: returns 1 if a function was found, 0 if not
 */
int is_builtin(char **argv, char *buffer)
{
	int i = 0;
	builtin_t builtins[] = {
		{"env", print_env},
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
