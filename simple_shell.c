#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>

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
	char *empty_string;
	
	if (!environ)
	{
		printf("_getenv null case");
		return (NULL);
	}
		
	if (environ[0] == NULL)
	{
		empty_string = malloc(sizeof(char) * 1);
		empty_string[0] = '\0';
		return (empty_string);
	}
	while (environ[i])
	{
		var = strdup(environ[i]);
		if (!var)
		{
			printf("var check");
			return (NULL);
		}
			
		token = strtok(var, "=");
		if(strcmp(name, token) == 0)
		{
			token = strtok(NULL, "=");
			if (!token)
			{
				free(var);
				empty_string = malloc(sizeof(char) * 1);
				empty_string[0] = '\0';
				printf("fuck it check");
				return (empty_string);
			}
			path = strdup(token);
			if (!path)
			{
				free(var);
				printf("middle _getenv check");
				return (NULL);
			}
			free(var);
			return(path);
		}
		free(var);
		i++;
	}
	printf("last _getenv check");
	return (NULL);
}

void free_all(char *buffer, char **argv, char *full_path, char *valid_path)
{
	free(buffer);
	free(argv);
	if (full_path)
		free(full_path);
	if (valid_path)
		free(valid_path);

}

int main(int ac, char **av)
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
	int error_code = 0;

	(void)ac;

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
		full_path = _getenv("PATH");
		if (!full_path)
			full_path = strdup("/bin");
		else if (*full_path == '\0')
		{
			fprintf(stderr, "%s: 1: %s: not found\n", av[0], argv[0]);
			free_all(buffer, argv, full_path, NULL);
			error_code = 127;
			continue;

		}
		valid_path = find_exec(full_path, argv[0]);
		if (!valid_path)
		{
			perror("Error");
			free_all(buffer, argv, full_path, NULL);
			continue;
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

				continue;
			}
		}
		else
		{
			wait(&status);
			error_code = WEXITSTATUS(status);
			free_all(buffer, argv, full_path, valid_path);
		}
	}
	return (0);
}