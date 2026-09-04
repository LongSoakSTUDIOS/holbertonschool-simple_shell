#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "main.h"
#include <errno.h>
/**
 * _get_env_index - function that retrieves the index
 * of an enviornment variable given the name
 * @name: name of the variable to find
 *
 * Return: returns the index if found, -1 if not
 */
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
/**
 * create_new_env_var - function that creates a new envrionment variable
 * by dynamically allocating a new enviornment, copying the previous one
 * and appending a new dynamically allocated variable to the end.
 * The function also frees the previous environment if the function has been
 * called before
 * @argv: tokenized commands from terminal input
 */
void create_new_env_var(char **argv)
{
	char *new_var;
	char **new_env;
	int size = 0;
	int i = 0;
	static int is_malloced = 0;

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
	new_env = malloc((size + 1) * sizeof(char *));
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
	if (is_malloced == 1)
		free(environ);
	else
		is_malloced = 1;
	environ = new_env;
}
/**
 * _setenv - function that sets a new enviornment variable if it doesn't
 * already exits, or overwrites the value of an existing one
 * @argv: tokenized commands from terminal input
 */
void _setenv(char **argv)
{
	int index;
	char *new_var;
	
	if (argc != 3)
	{
		fprintf(stderr, "hsh: setenv: wrong amount of arguments\n");
		errno = 7;
		return;
	}
	index = _get_env_index(argv[1]);
	if (index == -1)
	{
		create_new_env_var(argv);
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
