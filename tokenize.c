#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "main.h"

void check_exit(char *token, int *error_code, char *buffer, char **argv)
{
	if (token && strcmp(token, "exit") == 0)
	{
		token = strtok(NULL, " ");
		if (token)
		{
			free_all(buffer, argv, NULL, NULL);
			*error_code = atoi(token);
			exit(*error_code);
		}
		free_all(buffer, argv, NULL, NULL);
		exit(*error_code);
	}
}

char **tokenize(char *buffer, int *error_code)
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
		token = strtok(buffer, " ");
		check_exit(token, error_code, buffer, argv);
		i = 0;
		while (token != NULL)
		{
			argv[i] = token;
			token = strtok(NULL, " ");
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
