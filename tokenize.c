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
 * check_exit - compares the provided token for the literal string
 * exit and if there is a paremeter given
 * @token: single string that has been tokenized from buffer
 * @buffer: entire string input from user
 * @argv: tokenized strings from buffer split by a space separator
 * @av: an array holding the arguments passed to the shell
 *
 * Return: nothing
 */
void check_exit(char *token, char *buffer, char **argv, char **av)
{
	if (token && strcmp(token, "exit") == 0)
	{
		token = _strtok(NULL, " ");
		if (token)
		{
			error_code = _atoi(token);
			if (error_code < 0)
			{
				fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", av[0], token);
				error_code = 2;
			}
		}
		free_all(buffer, argv, NULL, NULL);
		if (environ_is_heap)
			free(environ);
		exit(error_code);
	}
}

/**
 * tokenize - uses strtok to split the full input buffer into individual
 * strings on a space separator
 * @buffer: a string of the users input
 * @av: an array holding the arguments passed to the shell, used for
 * exit to print a custom error
 *
 * Return: An array of strings containing the users full input on success,
 * NULL on failure
 */
char **tokenize(char *buffer, char **av)
{
		int i = 0;
		char **argv = NULL;
		char *token;

		argc = 0;
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
		check_exit(token, buffer, argv, av);
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
