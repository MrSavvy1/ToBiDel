#include "shell.h"

/**
 * main - Entry point to the shell program
 *
 * Return: 0 if success, 1 on failure
 */
int main(void)
{
	pid_t pid;
	int status, exec_status, count;
	size_t n;
	char **cmd, *buf, *full_path;
	int exit_int;

	program data;  // Declare an instance of the data structure
 data.tokens = NULL;    // Initialize its members appropriately
 data.command_name = NULL;

	buf = NULL;
	n = 0;
	count = 0;
	while (1)
	{
		signal(SIGINT, handle_signal);
		/* Write prompt */
		write(STDIN_FILENO, "Fizz=->> ", 9);

		/* Get command; if command is EOF, break */
		if (getline(&buf, &n, stdin) == -1)
		{
			write(STDIN_FILENO, "\n", 1);
			break;
		}

		/* Parse line and check command here */
		cmd = tokenize(buf, " \t\n");
		if (cmd[0] == NULL)
		{
			count++;
			continue;
		}
		if (_strcmp(cmd[0], "exit") == 0)
		{
				exit_int = 98;
				built_exit(&data, exit_int);
				/* The execution will not reach here if "exit" is called */
			}

		/* Creates a new process */
		pid = fork();
		if (pid == -1)
		{
			free(cmd);
			perror("Failed to fork");
			return (1);
		}

		/* Only execute this part in the child process */
		if (pid == 0)
		{
			/* cmd = tokenize(buf, " \t\n"); */
			if ((full_path = in_path(cmd[0])))
			{
				exec_status = execve(full_path, cmd, environ);
			}
			else
				exec_status = execve(cmd[0], cmd, environ);
			if (exec_status == -1)
			{
				free(cmd);
				perror("execve");
				return (1);
			}
			free(cmd);
		}
		/* Execute this part in the parent process which is the shell */
		else
		{
			signal(SIGINT, handle_signal2);
			waitpid(pid, &status, 0);
		}
		count++;
	}
	free(buf);
	return (0);
}
