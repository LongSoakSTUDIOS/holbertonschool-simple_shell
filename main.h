#ifndef MAIN_H
#define MAIN_H

extern char **environ;

int argc;

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
char *fill_buffer();
char **tokenize(char *buffer, char **av);
char *is_path(char **argv, char *buffer);
int is_builtin(char **argv, char *buffer);
char *get_full_path(char **av, char **argv, char *buffer);
char *get_valid_path(char **av, char **argv, char *buffer, char *fp);
void spawn_child(char **argv, char *buffer, char *full_path, char *valid_path);
char *_strtok(char *src, const char *delims);
int _atoi(char *s);
void _setenv(char **argv);

#endif
