#include "shell.h"

int main(void)
{
				size_t n;
				char *buf;
				int count;

				buf = NULL;
				n = 0;
				count = 0;

				program data;
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

								process_input(buf, &data, &count);
				}

				free(buf);
				return 0;
}

void process_input(char *buf, program *data, int *count)
{
				char **cmd;
				int status, exit_int;
				pid_t pid;

				cmd = tokenize(buf, " \t\n");
				if (cmd[0] == NULL)
				{
								(*count)++;
								return;
				}

				if (_strcmp(cmd[0], "exit") == 0)
				{
								exit_int = 98;
								built_exit(data, exit_int);
				}

				pid = create_process(&cmd);
				if (pid == -1)
				{
								free_and_error(cmd, "Failed to fork");
								exit(1);
				}
					

				execute_process(pid, &status, cmd);
				(*count)++;
}


pid_t create_process(char ***cmd)
{
				char *full_path;
				pid_t pid = fork();
				if (pid == 0)
				{
								
								execute_child_process(cmd, &full_path);
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

void execute_child_process(char ***cmd, char **full_path)
{
				int exec_status;
					*full_path = in_path((*cmd)[0]);
				if (full_path)
				{
								exec_status = execve(*full_path, *cmd, environ);
				}
				else
				{
								exec_status = execve((*cmd)[0], *cmd, environ);
				}

				if (exec_status == -1)
				{
								free_and_error(*cmd, "execve");
								_exit(EXIT_FAILURE);
				}

				free(*cmd);
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



// void change_directory(char **args) {
// 		char *path = args[1];

// 		if (path == NULL || _strcmp(path, "~") == 0) {
// 				// If no argument or "~" is given, change to home directory
// 				path = getenv("HOME");
// 		} else if (_strcmp(path, "-") == 0) {
// 				// If "-" is given, change to the previous directory
// 				path = getenv("OLDPWD");
// 		}

// 		if (chdir(path) != 0) {
// 				perror("cd");
// 		} else {
// 				// Update the environment variable PWD
// 				char current_path[PATH_MAX];
// 				if (getcwd(current_path, sizeof(current_path)) != NULL) {
// 						setenv("PWD", current_path, 1);
// 				}
// 		}
// }