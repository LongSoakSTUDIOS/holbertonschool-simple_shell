#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "main.h"
#include <errno.h>


int _get_env_index(const char *name)
{
	int i = 0;
	char *token;
	char *var;
	
	while (environ[i])
	{
		var = strdup(environ[i]);
		token = strtok(var, "=");
		if(strcmp(name, token) == 0)
		{
			free(var);
			return(i);
		}
		free(var);
		i++;
	}
	return (-1);
}

void _setenv(char **argv)
{
	int index;
	char *new_var;
	char **new_env;
	int size = 0;
	int i = 0;
	
	if (argc != 3)
	{
		fprintf(stderr, "hsh: setenv: wrong amount of arguments\n");
		errno = 7;
		return;
	}
	index = _get_env_index(argv[1]);
	if (index == -1)
	{
		new_var = malloc(strlen(argv[1]) + strlen(argv[2]) + 2);
		if (!new_var)
		{
			errno = -1;
			perror("Error");
			return;
		}
		sprintf(new_var, "%s=%s", argv[1], argv[2]);
		while(environ[size])
			size++;
		size++;
		new_env = malloc(size + 1 * sizeof(char *));
		if (!new_env)
		{
			errno = -1;
			perror("Error");
			return;
		}
		while (environ[i])
		{
			new_env[i] = environ[i];
			i++;
		}
		new_env[i] = new_var;
		new_env[i + 1] = NULL;
		environ = new_env;
		return;
	}
	else
	{
		new_var = malloc(strlen(argv[1]) + strlen(argv[2]) + 2);
		if (!new_var)
		{
			errno = -1;
			perror("Error");
			return;
		}
		sprintf(new_var, "%s=%s", argv[1], argv[2]);
		environ[index] = new_var;
	}
}