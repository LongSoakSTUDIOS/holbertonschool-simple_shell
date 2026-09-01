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



int main(int ac, char **av)
{
	pid_t child_id;
	ssize_t characters_read;
	char *token = NULL, *buffer = NULL, *valid_path = NULL, *full_path = NULL;
	size_t size;
	char **argv = NULL;
	int argc = 0, status, i = 0, error_code = 0, j = 0, found = 0;
	int path_flag = 0;
	builtin_t builtins[] = {
		{"env" , print_env},
		{NULL, NULL}
	};
	
	(void)ac;

	signal(SIGINT, signal_handler);

	while (1)
	{
		path_flag = 0;
		buffer = NULL;
		size = 0;
		argv = NULL;
		if (isatty(0) == 1)
			printf("$");
		characters_read = getline(&buffer, &size, stdin);
		if (characters_read < 0)
		{
			free_all(buffer, NULL, NULL, NULL);
			if (characters_read == EOF)
			{
				exit(error_code);
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
		argv = malloc(sizeof(char *) * (argc + 1));
		if (argv == NULL)
		{
			free_all(buffer, NULL, NULL, NULL);
			perror("Malloc error");
			return (-1);
		}
		token = strtok(buffer, " ");
		if (token && strcmp(token, "exit") == 0)
		{
			token = strtok(NULL, " ");
			if (token)
			{
				error_code = atoi(token);
				exit(error_code);
			}
			free_all(buffer, argv, NULL, NULL);
			exit(error_code);
		}
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
			free_all(buffer, argv, NULL, NULL);
			continue;
		}

		if (strchr(argv[0], '/') != NULL)
		{
			if (access(argv[0], X_OK) == 0)
			{
				valid_path = strdup(argv[0]);
				path_flag = 1;
				if (valid_path == NULL)
				{
					perror("Error");
					free_all(buffer, argv, NULL, NULL);
					continue;
				}
			}
			else
			{
				perror("Error");
				free_all(buffer, argv, NULL, NULL);
				continue;
			}
			
		}
		else
		{
			j = 0;
			while (builtins[j].command != NULL)
			{
				if (strcmp(builtins[j].command, argv[0]) == 0)
				{
					builtins[j].function(argv);
					found = 1;
					break;
				}
				j++;
			}
			if (found)
			{
				free_all(buffer, argv, NULL, NULL);
				continue;
			}

			full_path = _getenv("PATH");
			if (!full_path || *full_path == '\0')
			{
				fprintf(stderr, "%s: 1: %s: not found\n", av[0], argv[0]);
				free_all(buffer, argv, full_path, NULL);
				error_code = 127;
				continue;
			}
			valid_path = find_exec(full_path, argv[0]);
			if (!valid_path)
			{
				fprintf(stderr, "%s: 1: %s: not found\n", av[0], argv[0]);
				free_all(buffer, argv, full_path, NULL);
				error_code = 127;
				continue;
			}
		}

		child_id = fork();
		if (child_id == -1)
		{
			perror("Error:");
			free_all(buffer, argv, full_path, valid_path);
			return (1);
		}
		if (child_id == 0)
		{
			if (execve(valid_path, argv, NULL) == -1)
			{
				printf("hello");
				perror("Error:");
				free_all(buffer, argv, full_path, valid_path);

				exit(error_code);
			}
		}
		else
		{
			wait(&status);
			error_code = WEXITSTATUS(status);
			if (path_flag == 0)
				free_all(buffer, argv, full_path, valid_path);
			else
				free_all(buffer, argv, NULL, valid_path);
		}
	}
	return (0);
}