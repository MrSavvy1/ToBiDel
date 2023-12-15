#include "shell.h"

int main(void)
{
				shell_loop();
				return 0;
}

void shell_loop(void)
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
								signal(SIGINT, handle_signal);
								write(STDIN_FILENO, "Fizz=->> ", 9);

								if (getline(&buf, &n, stdin) == -1)
								{
												write(STDIN_FILENO, "\n", 1);
												break;
								}

								cmd = tokenize(buf, " \t\n");
								if (cmd[0] == NULL)
								{
												count++;
												continue;
								}

								if (_strcmp(cmd[0], "exit") == 0)
								{
												built_exit(&data);
								}

								pid = fork();
								if (pid == -1)
								{
												free_and_error(cmd, "Failed to fork");
												return;
								}

								if (pid == 0)
								{
												execute_child_process(cmd, &full_path, &data);
								}
								else
								{
												execute_parent_process(pid, &status);
								}

								count++;
				}

				free(buf);
}

void execute_child_process(char **cmd, char **full_path, program *data)
{
				int exec_status;

				if ((full_path = in_path(cmd[0])))
				{
								exec_status = execve(*full_path, cmd, environ);
				}
				else
				{
								exec_status = execve(cmd[0], cmd, environ);
				}

				if (exec_status == -1)
				{
								free_and_error(cmd, "execve");
								_exit(EXIT_FAILURE);
				}

				free(cmd);
}

void execute_parent_process(pid_t pid, int *status)
{
				signal(SIGINT, handle_signal2);
				waitpid(pid, status, 0);
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
