#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT 100

int main() {
				char input[MAX_INPUT];

				while (1) {
								// Display prompt and wait for user input
								printf("MyShell> ");
								if (fgets(input, MAX_INPUT, stdin) == NULL) {
												// Handle Ctrl+D (end of file)
												printf("\nExiting shell...\n");
												break;
								}

								// Remove newline character
								input[strcspn(input, "\n")] = '\0';

								// Tokenize the command and arguments
								char *token = strtok(input, " ");
					printf("token: %s\n", token);
								char *args[MAX_INPUT];  // Store arguments

								int i = 0;
								while (token != NULL) {
												args[i++] = token;
												token = strtok(NULL, " ");
								}
								args[i] = NULL;  // Null-terminate the arguments array
					printf("token: %s\n", token);
								if (args[0] != NULL) {
												// Check if the command exists in PATH
												char *path = getenv("PATH");
												char *path_token = strtok(path, ":");

												while (path_token != NULL) {
																// Form potential full path
																char full_path[MAX_INPUT];
																snprintf(full_path, sizeof(full_path), "%s/%s", path_token, args[0]);

																// Check if the command is executable
																if (access(full_path, X_OK) == 0) {
																				pid_t pid = fork();

																				if (pid == 0) {
																								// In child process
																								execve(full_path, args, NULL);
																								// If execve fails, print an error
																								perror("Error");
																								exit(EXIT_FAILURE);
																				} else if (pid < 0) {
																								perror("Fork failed");
																				} else {
																								// In parent process, wait for child to finish
																								wait(NULL);
																				}

																				break;
																}

																path_token = strtok(NULL, ":");
												}

												// If the loop completes, the command was not found
												if (path_token == NULL) {
																fprintf(stderr, "Command not found: %s\n", args[0]);
												}
								}
				}

				return 0;
}