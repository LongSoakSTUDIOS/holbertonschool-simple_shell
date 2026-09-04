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
 * spawn_child - creates a child process that will execute the command
 * found from the input string by the user
 * @argv: tokenized strings from buffer split by a space separator
 * @buffer: entire string input from user
 * @full_path: a string containing the PATH environ variable
 * @valid_path: a string containing the path to the executable
 *
 * Return: nothing
 */
void spawn_child(char **argv, char *buffer, char *full_path, char *valid_path)
{
	pid_t child_id;
	int status;

	child_id = fork();
	if (child_id == -1)
	{
		perror("Error");
		free_all(buffer, argv, full_path, valid_path);
		exit(1);
	}
	if (child_id == 0)
	{
		if (execve(valid_path, argv, NULL) == -1)
		{
			perror("Error");
			free_all(buffer, argv, full_path, valid_path);
			exit(error_code);
		}
	}
	else
	{
		wait(&status);
		error_code = WEXITSTATUS(status);
		free_all(buffer, argv, full_path, valid_path);
	}
}
