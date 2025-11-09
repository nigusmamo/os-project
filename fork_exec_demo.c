#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

void print_process_info(const char *process_type);

int main()
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

    printf("=== Interactive Process Execution Terminal ===\n");
    printf("Type 'exit' to quit\n\n");

    while (1)
    {
        printf(">> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = 0;
        if (strlen(input) == 0)
            continue;

        if (strcmp(input, "exit") == 0)
            break;

        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL && i < MAX_ARGS - 1)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        pid_t child_pid = fork();

        if (child_pid < 0)
        {
            perror("fork() failed");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0)
        {
            print_process_info("Child");
            if (execvp(args[0], args) == -1)
            {
                perror("execvp() failed");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            print_process_info("Parent");
            int status;
            waitpid(child_pid, &status, 0);
            if (WIFEXITED(status))
                printf("Parent: Child exited normally with status %d\n\n", WEXITSTATUS(status));
            else
                printf("Parent: Child terminated abnormally\n\n");
        }
    }

    printf("Exiting Interactive Terminal...\n");
    return 0;
}

void print_process_info(const char *process_type)
{
    printf("%s Process:\n", process_type);
    printf("  - PID: %d\n", getpid());
    printf("  - PPID: %d\n", getppid());
    printf("  - Process Group ID: %d\n", getpgrp());
    printf("  - User ID: %d\n", getuid());
    printf("  - Effective User ID: %d\n", geteuid());
}
