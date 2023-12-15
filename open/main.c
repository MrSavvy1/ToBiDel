#include "shell.h"

int main(void)
{
				pid_t pid;
				int status, count;
				size_t n;
				char **cmd, *buf, *full_path;
				program data;

				buf = NULL;
				n = 0;
				count = 0;
				data.tokens = NULL;
				data.command_name = NULL;

				while (1)
				{
								setup_shell(&buf, &n);
								if (handle_input(&buf, &n, &data, &count))
												break;

								pid = create_process(&cmd, &full_path, &data, &status);

								if (pid == -1)
								{
												free_and_error(cmd, "Failed to fork");
												return (1);
								}

								execute_process(pid, &status, cmd);
								count++;
				}

				free(buf);
				return (0);
}

void setup_shell(char **buf, size_t *n)
{
				signal(SIGINT, handle_signal);
				write(STDIN_FILENO, "Fizz=->> ", 9);
				if (getline(buf, n, stdin) == -1)
				{
								write(STDIN_FILENO, "\n", 1);
				}
}

int handle_input(char **buf, size_t *n, program *data, int *count)
{
				int exit_int;
				char **cmd = tokenize(*buf, " \t\n");
				if (cmd[0] == NULL)
				{
								(*count)++;
								return 0;
				}

				if (_strcmp(cmd[0], "exit") == 0)
				{
								exit_int = 98;
								built_exit(data, exit_int);
								return 1;
				}

				return 0;
}

pid_t create_process(char ***cmd, char **full_path, program *data, int *status)
{
				pid_t pid = fork();
				if (pid == 0)
				{
								handle_child_process(cmd, full_path, data);
				}
				return pid;
}

void execute_process(pid_t pid, int *status, char **cmd)
{
				if (pid != 0)
				{
								waitpid(pid, status, 0);
								free(cmd);
				}
}

void free_and_error(char **cmd, const char *error_message)
{
				perror(error_message);

				if (cmd != NULL)
				{
								char **temp = cmd;
								while (*temp != NULL)
								{
												free(*temp);
												temp++;
								}
								free(cmd);
				}

				exit(EXIT_FAILURE);
}

void handle_child_process(char ***cmd, char **full_path, program *data)
{
				pid_t pid;
				int status;

				pid = fork();
				if (pid == 0)
				{
								// In the child process
								if (*full_path != NULL)
								{
												// Check if the command is executable
												if (access(*full_path, X_OK) == 0)
												{
																execve(*full_path, *cmd, environ);
																perror("execve");
												}
												else
												{
																perror("access");
												}
								}
								else
								{
												perror("execve");
								}

								// Exit the child process with an error code
								free_and_error(*cmd, "Failed to execute command");
								_exit(EXIT_FAILURE);
				}
				else if (pid < 0)
				{
								// Handle fork failure
								free_and_error(*cmd, "Failed to fork");
				}
				else
				{
								// In the parent process, wait for the child to finish
								waitpid(pid, &status, 0);
								free(*cmd);
				}
}