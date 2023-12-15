#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0

typedef struct program{
	char **tokens;
	char *command_name;
} program;

char **tokenize(char *str, char *delim);
void handle_signal(int);
void handle_signal2(int);
char *in_path(char *);
int _strcmp(const char *s1, const char *s2);
int built_exit(program *data, int exit_int);

void setup_shell(char **buf, size_t *n);
int handle_input(char **buf, size_t *n, program *data, int *count);
pid_t create_process(char ***cmd, char **full_path, program *data, int *status);
void execute_process(pid_t pid, int *status, char **cmd);
void free_and_error(char **cmd, const char *error_message);
void handle_child_process(char ***cmd, char **full_path, program *data);

extern char **environ;

#endif
