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
 * free_all -
 * @buffer:
 * @argv:
 * @full_path:
 * @valid_path:
 * 
 * Return: 
 */
void free_all(char *buffer, char **argv, char *full_path, char *valid_path)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	if (argv)
	{
		free(argv);
		argv = NULL;
	}
	if (full_path)
	{
		free(full_path);
		full_path = NULL;
	}
	if (valid_path)
	{
		free(valid_path);
		valid_path = NULL;
	}
}