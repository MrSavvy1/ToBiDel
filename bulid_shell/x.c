#include "shell.h"

#define MAX_INPUT 100



int main() {
				pid_t pid;
				int status;
				size_t n;
				char **cmd, *buf;

				buf = NULL;
				n = 0;

				while (1) {
								// Write prompt
								printf("MyShell> ");

								buf = NULL;  // Reset buf to avoid garbage or residue
								n = 0;

								// Get command; if command is EOF, break
								if (getline(&buf, &n, stdin) == -1) {
												printf("\nExiting shell...\n");
												break;
								}

								// Remove newline character
								buf[strcspn(buf, "\n")] = '\0';

								// Tokenize the command and arguments
								cmd = tokenize(buf, " \t\n");

								// Create a new process to execute the command
								pid = fork();

								if (pid == -1) {
												perror("Failed to fork");
												free(buf);
												free(cmd);
												exit(EXIT_FAILURE);
								} 
								else if (pid == 0) {
												// In child process
												execvp(cmd[0], cmd);

												// Handle failed execution
												perror("Error");
												free(buf);
												free(cmd);
												exit(EXIT_FAILURE);
								} 
								else {
												// In parent process, wait for child to finish
												waitpid(pid, &status, 0);
								}

								free(buf);  // Free allocated memory
								free(cmd);
				}

				return 0;
}
