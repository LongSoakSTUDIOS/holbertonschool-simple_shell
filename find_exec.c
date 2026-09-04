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
 * find_exec - function that looks for an executable that
 * matches the command given
 * @full_path: path variable containing all valid paths to check from
 * @command: command to look for
 *
 * Return: returns the valid path to the executable, or NULL if not found
 */
char *find_exec(char *full_path, char *command)
{
	char *token;
	char *temp;

	if (!command || !full_path)
		return (NULL);
	token = _strtok(full_path, ":");
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
		token = _strtok(NULL, ":");
		free(temp);
	}
	return (NULL);
}
