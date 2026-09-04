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
 * signal_handler - on SIGINT signal the shell will move to a new line,
 * reprint the prompt and flush the stdout
 * @signum: the signal number received (expected to be SIGINT)
 *
 * Return: nothing
 */
void signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		printf("$");
		fflush(stdout);
	}
}
