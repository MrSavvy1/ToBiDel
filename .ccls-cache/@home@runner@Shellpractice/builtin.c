#include "shell.h"

/**
	* builtin_exit - handles the exit built-in command
	* @data: struct for the program's data
	* Return: 0 to exit the shell
	*/
int builtin_exit(data_of_program *data)
{
				/* Additional cleanup or handling before exiting, if needed */
				free(data->tokens);
				free(data->command_name);

				exit(0);
}
