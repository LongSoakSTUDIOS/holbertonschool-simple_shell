#ifndef MAIN_H
#define MAIN_H

typedef struct builtin_s
{
	char *command;
	void (*function)(char **);

}	builtin_t;

void free_all(char *buffer, char **argv, char *full_path, char *valid_path);
void print_env(char **argv);
char *find_exec(char *full_path, char *command);
char *_getenv(const char *name);
void signal_handler(int signum);

#endif