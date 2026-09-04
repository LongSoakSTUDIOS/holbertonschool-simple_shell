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
 * print_env - function that prints the current environment
 * @argv: tokenized arguments sent from user input within our shell(voided)
 */
void print_env(char **argv)
{
	int i = 0;

	(void)argv;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
