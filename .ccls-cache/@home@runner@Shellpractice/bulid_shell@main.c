#include "shell.h"

#define MAX_INPUT 100

int main(void) {
    pid_t pid;
    int status, exec_status;
    size_t n;
    char **cmd, *buf;
    char full_path[MAX_INPUT];
    char *path_token ;

    buf = NULL;
    n = 0;

    while (1) {
        /* Write prompt */
        write(STDIN_FILENO, "Fizz=->> ", 9);

        /* Get command; if command is EOF, break */
        if (getline(&buf, &n, stdin) == -1) {
            write(STDIN_FILENO, "\n", 1);
            break;
        }

        /* Remove newline character from the input */
        buf[strcspn(buf, "\n")] = '\0';

        /* Parse line and check command here */
        cmd = tokenize(buf, " \t\n");

        if (cmd[0] != NULL) {
            // Check if the command exists in PATH
            char *path = getenv("PATH");
            path_token = strtok(path, ":");
            

            int commandExecuted = 0; // Flag to check if a command has been executed

            while (path_token != NULL) {
                // Form potential full path
                char full_path[MAX_INPUT];
                snprintf(full_path, sizeof(full_path), "%s/%s", path_token, cmd[0]);
                            printf("full_path %s\n", full_path);

                // Check if the command is executable
                if (access(full_path, X_OK) == 0) {
                    
                    /* Creates a new process */
                    pid = fork();
                            printf("pid is: %d\n", pid);

                    if (pid == -1) {
                        perror("Failed to fork");
                        return 1;
                    } else if (pid == 0) {
                        /* Execute this part in the child process */
                        exec_status = execve(full_path, cmd, environ);

                        if (exec_status == -1) {
                            perror("execve");
                            exit(EXIT_FAILURE);  // Exit with an error status
                        }
                        
                    } else {
                        /* Execute this part in the parent process (shell) */
                        waitpid(pid, &status, 0);
                        commandExecuted = 1; // Set the flag to true
                        break;  // Break from the loop after waiting for the child process
                    // 
                    }
                }
                                path_token = strtok(NULL, ":");
                            printf("The SECOND path_token: %s\n", path_token);
            }
            // If the loop completes and no command was executed, print an error
            if (!commandExecuted) {
                fprintf(stderr, "Command not found: %s\n", cmd[0]);
            
            }

            free(cmd);
            // Free memory allocated for cmd
        }
    }

    free(buf);
    
    return 0;
}
