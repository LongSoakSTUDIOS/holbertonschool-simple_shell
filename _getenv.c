#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "main.h"

extern char **environ;

char *_getenv(const char *name)
{
	int i = 0;
	char *token;
	char *var;
	char *path;
	char *empty_string;
	
	if (!environ)
	{
		printf("_getenv null case");
		return (NULL);
	}
		
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
		{
			return (NULL);
		}
			
		token = strtok(var, "=");
		if(strcmp(name, token) == 0)
		{
			token = strtok(NULL, "=");
			if (!token)
			{
				free(var);
				empty_string = malloc(sizeof(char) * 1);
				empty_string[0] = '\0';
				return (empty_string);
			}
			path = strdup(token);
			if (!path)
			{
				free(var);
				return (NULL);
			}
			free(var);
			return(path);
		}
		free(var);
		i++;
	}
	return (NULL);
}