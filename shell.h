#ifndef SHELL_H
#define SHELL_H

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
/* for breaking input into tokens */
char **tokenize(char *str, char *delim);
/* for formatting the token to be used in execve */
int _snprintf(char *buffer, size_t size, const char *format, ...);
/* for getting the path of the command */
char* _getenv(const char* var_name);
/* for executing the command */

/*int execute_command(char** cmd);*/

/* holds a pointer to an array of strings ending with a null character */
extern char **environ;

#endif
