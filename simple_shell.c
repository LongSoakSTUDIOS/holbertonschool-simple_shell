#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>

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

char *find_exec(char *full_path, char *command)
{
	char *token;
	char *temp;

	if (!full_path || !command)
		return (NULL);
	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
		{
			temp = strdup(command);
			return (temp);
		}
		return (NULL);
	}
	token = strtok(full_path, ":");
	while (token != NULL)
	{
		temp = malloc(strlen(token) + strlen(command) + 2);
		strcpy(temp, token);
		strcat(temp, "/");
		strcat(temp, command);
		if (access(temp, X_OK) == 0)
		{
			return (temp);
		}
		token = strtok(NULL, ":");
		free(temp);
	}
	return (NULL);
}

char *_getenv(const char *name)
{
	int i = 0;
	char *token;
	char *var;
	char *path;
	
	if (!environ)
		return (NULL);
	while (environ[i])
	{
		var = strdup(environ[i]);
		if (!var)
			return (NULL);
		token = strtok(var, "=");
		if(strcmp(name, token) == 0)
		{
			token = strtok(NULL, "=");
			if (!token)
				return (NULL);
			path = strdup(token);
			if (!path)
				return (NULL);
			free(var);
			return(path);
		}
		free(var);
		i++;
	}
	return (NULL);
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
	char *valid_path = NULL;
	char *full_path = NULL;

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
			if (characters_read == EOF)
			{
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
		argv = malloc(sizeof(char *) * (argc + 1));
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
			free(buffer);
			continue;
		}
		full_path = _getenv("PATH");
		if (!full_path)
			full_path = strdup("/bin");
		valid_path = find_exec(full_path, argv[0]);
		if (!valid_path)
		{
			perror("Error: Ex");
			free(full_path);
			free(argv);
			free(buffer);
			continue;
		}
		child_id = fork();
		if (child_id == -1)
		{
			perror("Error:");
			free(valid_path);
			free(full_path);
			free(argv);
			free(buffer);
			return (1);
		}
		if (child_id == 0)
		{
			if (execve(valid_path, argv, NULL) == -1)
			{
				perror("Error:");
				free(valid_path);
				free(full_path);
				free(argv);
				free(buffer);
				exit(127);
			}
		}
		else
		{
			wait(&status);
			free(valid_path);
			free(full_path);
			free(buffer);
			free(argv);
		}
	}
	return (0);
}