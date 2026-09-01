#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "main.h"

void spawn_child(char **argv, char *buffer, int *error_code,
	char *full_path, int path_flag, char *valid_path)
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
			exit(*error_code);
		}
	}
	else
	{
		wait(&status);
		*error_code = WEXITSTATUS(status);
		if (path_flag == 0)
			free_all(buffer, argv, full_path, valid_path);
		else
			free_all(buffer, argv, NULL, valid_path);
	}
}