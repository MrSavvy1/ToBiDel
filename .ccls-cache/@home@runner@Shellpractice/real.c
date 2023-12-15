#include "shell.h"

void change_directory(char **args) {
    char *dir_home = getenv("HOME");
    char *dir_old = NULL;
    char old_dir[128] = {0};
    int error_code = 0;

    if (args[1]) {
        if (_strcmp(args[1], "-") == 0) {
            dir_old = getenv("OLDPWD");
            if (dir_old) {
                error_code = chdir(dir_old);
            }
            printf("%s\n", getenv("PWD"));
            return;
        } else {
            error_code = chdir(args[1]);
        }
    } else {
        if (!dir_home) {
            if (getcwd(old_dir, sizeof(old_dir)) != NULL) {
                dir_home = old_dir;
            }
        }
        error_code = chdir(dir_home);
    }

    if (error_code == 0) {
        char current_path[PATH_MAX];
        if (getcwd(current_path, sizeof(current_path)) != NULL) {
            setenv("PWD", current_path, 1);
        }
    } else {
        perror("cd");
    }
}

void process_input(char *buf, program *data, int *count) {
    char **cmd;
    int status, exit_int;
    pid_t pid;

    cmd = tokenize(buf, " \t\n");
    if (cmd[0] == NULL) {
        (*count)++;
        return;
    }

    if (_strcmp(cmd[0], "exit") == 0) {
        exit_int = 98;
        built_exit(data, exit_int);
    } else if (_strcmp(cmd[0], "cd") == 0) {
        // Handle cd command
        change_directory(cmd);
    } else {
        pid = create_process(&cmd);
        if (pid == -1) {
            free_and_error(cmd, "Failed to fork");
            exit(1);
        }

        execute_process(pid, &status, cmd);
    }

    (*count)++;
}

// The rest of your existing code remains unchanged
