#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		printf("$");
		fflush(stdout);
	}
}

int main(void)
{
	pid_t child_id;
	ssize_t characters_read;
	char *token = NULL, *buffer = NULL;
	size_t size;
	char **argv = NULL;
	int i = 0;
	int argc = 0;
	int status;

	signal(SIGINT, signal_handler);

	while (1)
	{
		buffer = NULL;
		size = 0;
		argv = NULL;
		if (isatty(0) == 1)
			printf("$");
		characters_read = getline(&buffer, &size, stdin);
		if (characters_read < 0)
		{
			free(buffer);
			if (feof(stdin))
			{
				printf("\n");
				return (0);
			}
			return (-1);
		}
		if (buffer[characters_read - 1] == '\n')
			buffer[characters_read - 1] = '\0';
		i = 0;
		argc = 0;
		while (buffer[i] != '\0')
		{
			if (buffer[i] == ' ')
				argc++;
			i++;
		}
		argc++;
		argv = malloc(sizeof(char *) * argc + 1);
		if (argv == NULL)
		{
			free(buffer);
			perror("Malloc error");
			return (-1);
		}
		token = strtok(buffer, " ");
		i = 0;
		while (token != NULL)
		{
			argv[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		argv[i] = NULL;
		if (argv[0] == NULL)
		{
			free(argv);
			continue;
		}
		child_id = fork();
		if (child_id == -1)
		{
			perror("Error:");
			free(argv);
			free(buffer);
			return (1);
		}
		if (child_id == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("Error:");
				exit(127);
			}
		}
		else
		{
			wait(&status);
			free(buffer);
			free(argv);
		}
	}

	return (0);
}