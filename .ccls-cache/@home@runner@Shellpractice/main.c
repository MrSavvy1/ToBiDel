#include "shell.h"
#define MAX_INPUT 100


/**
 * main - Entry point to the shell program
 *
 * Return: 0 if success, 1 on failure
 */
int main(void) {
  pid_t pid;
  int status, exec_status;
  size_t n;
  char **cmd, *buf, slash = '/';
  int commandExecuted = 0; // Flag to check if a command has been executed

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
    /* Parse line and check command here */
    cmd = tokenize(buf, " \t\n");
    /* check is cmd is null */
    if (cmd[0] != NULL) {
      /* Creates a new process */
      pid = fork();

      if (pid == -1) {
        free(cmd);
        perror("Failed to fork");
        return (1);
      }
      /* Only execute this part in the child process */
      else if (pid == 0) {

        // Check if the string starts with the specified character
        if (*cmd[0] != slash) {
          char *path = _getenv("PATH");
          char *path_token = strtok(path, ":");
									int commandExecuted =
              0; // Flag to check if a command has been executed

          while (path_token != NULL) {
            // Form potential full path
            char full_path[MAX_INPUT];
            _snprintf(full_path, sizeof(full_path), "%s/%s", path_token,
                            cmd[0]);
											// Check if the command is executable

            if (access(full_path, X_OK) == 0) {
              exec_status = execve(full_path, cmd, environ);
              printf("Value of exec_sta: %d\n", exec_status);
            }

            path_token = strtok(NULL, ":");
          }
          if (!commandExecuted) {
            free(cmd);
            perror("execve");
            return (1);
          }
        }

        else {
          exec_status = execve(cmd[0], cmd, environ);

          if (exec_status == -1) {
            free(cmd);
            perror("execve");
            return (1);
          }
        }
        free(cmd);
      }

      /* Execute this part in the parent process which is the shell */
      else {

        waitpid(pid, &status, 0);
        commandExecuted =
            1; // Set the flag to true
               // Break from the loop after waiting for the child process
               //
      }
    } else {
      perror("Error: No command entered");
    }
  }
  free(buf);
  return (0);
}