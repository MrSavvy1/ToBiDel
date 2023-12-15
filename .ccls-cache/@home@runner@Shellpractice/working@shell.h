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

	typedef struct data_of_program {
    char **tokens;
    char *command_name;
    /* Other members if present in your actual struct */
} data_of_program;


char **tokenize(char *str, char *delim);
void handle_signal(int);
void handle_signal2(int);
char *in_path(char *);
int builtin_exit(data_of_program *data);
int _strcmp(const char *s1, const char *s2);


extern char **environ;

#endif
