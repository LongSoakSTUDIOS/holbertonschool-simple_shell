#ifndef MAIN_H
#define MAIN_H

extern char **environ;

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
char *fill_buffer(int *error_code);
char **tokenize(char *buffer, int *error_code);
char *is_path(char **argv, char *buffer);
int is_builtin(char **argv, char *buffer);
char *get_full_path(char **av, char **argv, char *buffer, int *error_code);
char *get_valid_path(char **av, char **argv, char *buffer, int *ec, char *fp);
void spawn_child(char **av, char **argv, char *buffer, 
	int *error_code, char *full_path, int path_flag, char *valid_path);

#endif
