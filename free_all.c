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
 * free_all - function that frees all dynamically allocated variables at once
 * @buffer: buffer
 * @argv: string of strings with each tokenized string of the inputted command
 * @full_path: full path variable
 * @valid_path: path to the executable
 */
void free_all(char *buffer, char **argv, char *full_path, char *valid_path)
{
	if (buffer)
		free(buffer);
	if (argv)
		free(argv);
	if (full_path)
		free(full_path);
	if (valid_path)
		free(valid_path);
}
