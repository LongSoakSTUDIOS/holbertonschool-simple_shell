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
 * check_exit - 
 * @token:
 * @error_code:
 * @buffer:
 * @argv:
 * 
 * Return: nothing
 */
void check_exit(char *token, int *error_code, char *buffer, char **argv, char **av)
{
	if (token && strcmp(token, "exit") == 0)
	{
		token = _strtok(NULL, " ");
		if (token)
		{
			*error_code = _atoi(token);
			if (*error_code < 0)
			{
				fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", av[0], token);
				*error_code = 2;
			}
		}
		free_all(buffer, argv, NULL, NULL);
		exit(*error_code);
	}
}

/**
 * tokenize - 
 * @buffer:
 * @error_code:
 * 
 * Return: nothing
 */
char **tokenize(char *buffer, int *error_code, char **av)
{
		int i = 0;
		int argc = 0;
		char **argv = NULL;
		char *token;

		while (buffer[i] != '\0')
		{
			if (buffer[i] == ' ')
				argc++;
			i++;
		}
		argc++;
		argv = malloc(sizeof(char *) * (argc + 1));
		if (argv == NULL)
		{
			free_all(buffer, NULL, NULL, NULL);
			perror("Malloc error");
			return (NULL);
		}
		token = _strtok(buffer, " ");
		check_exit(token, error_code, buffer, argv, av);
		i = 0;
		while (token != NULL)
		{
			argv[i] = token;
			token = _strtok(NULL, " ");
			i++;
		}
		argv[i] = NULL;
		if (argv[0] == NULL)
		{
			free_all(buffer, argv, NULL, NULL);
			return (NULL);
		}
		return (argv);
}
