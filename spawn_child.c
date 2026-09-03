#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "main.h"

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
			exit(errno);
		}
	}
	else
	{
		wait(&status);
		errno = WEXITSTATUS(status);
		free_all(buffer, argv, full_path, valid_path);
	
	}
}