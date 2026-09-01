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

char *find_exec(char *full_path, char *command)
{
	char *token;
	char *temp;

	if (!command)
		return (NULL);
	if (!full_path)
	{
		return (NULL);
	}
	token = strtok(full_path, ":");
	while (token != NULL)
	{
		temp = malloc(strlen(token) + strlen(command) + 2);
		strcpy(temp, token);
		strcat(temp, "/");
		strcat(temp, command);
		if (access(temp, X_OK) == 0)
		{
			return (temp);
		}
		token = strtok(NULL, ":");
		free(temp);
	}
	return (NULL);
}