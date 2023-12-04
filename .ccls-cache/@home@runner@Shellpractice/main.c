#include "shell.h"

/**
	* main - Entry point to the shell program
	* 
	* Return: 0 if success, 1 on failure
	*/
int main(void)
{
	pid_t pid;
	int status, exec_status;
	size_t n;
	char **cmd, *buf;

	buf = NULL;
	n = 0;
	while (1)
	{
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

		/* Creates a new process */
		pid = fork();
		if (pid == -1)
		{
			free(cmd);
			perror("Failed to fork");
			return (1);
		}
		/* Only execute this part in the child process */
		else if (pid == 0)
		{
			/* parse command
			cmd = tokenize(buf, " \t\n");*/

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
			waitpid(pid, &status, 0);
	}
	free(buf);
	return (0);
}