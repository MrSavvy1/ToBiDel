#include "shell.h"
#define MAX_INPUT 100

char* _getenv(const char* var_name) {
				extern char **environ; 

				int var_len = 0;
				while (var_name[var_len] != '\0') {
								var_len++;
				}

				for (int i = 0; environ[i] != NULL; i++) {
								char* env_var = environ[i];

								int j = 0;
								while (var_name[j] != '\0' && env_var[j] == var_name[j]) {
												j++;
								}

								if (var_name[j] == '\0' && env_var[j] == '=') {
												
												return &env_var[j + 1];
								}
				}

				// Variable not found
				return NULL;
}

// int main() {
// 				const char* variable_name = "PATH";
// 				char* value = custom_getenv(variable_name);

// 				if (value != NULL) {
// 								printf("%s=%s\n", variable_name, value);
// 				} else {
// 								printf("Variable not found\n");
// 				}

// 				return 0;
// }
/*
int execute_command(char** cmd) {
    const char slash = '/';
    int exec_status = 0;
				int commandExecuted = 0;

    if (*cmd[0] != slash) {
        char* path = _getenv("PATH");
        char* path_token = strtok(path, ":");
          // Flag to check if a command has been executed

        while (path_token != NULL) {
            // Form potential full path
            char full_path[MAX_INPUT];
            _snprintf(full_path, sizeof(full_path), "%s/%s", path_token, cmd[0]);

            // Check if the command is executable
            if (access(full_path, X_OK) == 0) {
                exec_status = execve(full_path, cmd, environ);
                printf("Value of exec_sta: %d\n", exec_status);
													commandExecuted = 1; // Set the flag to true
            }

            path_token = strtok(NULL, ":");
        }

        if (!commandExecuted) {
            perror("execve");
            return 1;
        }
    }

    return commandExecuted;
}*/