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
 * path_variable - function that checks if the value
 * of an enviornment variable is NULL and creates a string with the value
 * @var: variable to check
 *
 * Return: returns a dynamically allocated string of size 1 in case the
 * value is NULL, a dynamically allocated string of the value if it exits
 * NULL if malloc fails
 */
char *path_variable(char *var)
{
	char *empty_string, *token, *path;

	token = _strtok(NULL, "=");
	if (!token)
	{
		empty_string = malloc(sizeof(char) * 1);
		empty_string[0] = '\0';
		return (empty_string);
	}
	path = strdup(token);
	if (!path)
		return (NULL);
	return (path);
}
/**
 * _getenv - function that returns the environment variable as a string
 * @name: name of the variable to find
 *
 * Return: returns an empty string if environment is empty, a dynamically
 * allocated empty string of size 1 if the environment variable 
 * exists but the value is NULL, or a dynamically allocated string of the
 * enviornment variable's value
 */
char *_getenv(const char *name)
{
	int i = 0;
	char *token, *empty_string, *var, *path;

	if (!environ)
		return (NULL);
	if (environ[0] == NULL)
	{
		empty_string = malloc(sizeof(char) * 1);
		empty_string[0] = '\0';
		return (empty_string);
	}
	while (environ[i])
	{
		var = strdup(environ[i]);
		if (!var)
			return (NULL);
		token = _strtok(var, "=");
		if (strcmp(name, token) == 0)
		{
			path = path_variable(var);
			free(var);
			return (path);
		}
		free(var);
		i++;
	}
	return (NULL);
}
