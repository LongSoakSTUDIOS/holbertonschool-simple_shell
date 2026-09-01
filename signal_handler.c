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

void signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		printf("$");
		fflush(stdout);
	}
}