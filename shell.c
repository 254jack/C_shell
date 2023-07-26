#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 512

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;
    int status;

    while (1)
    {
        printf("#cisfun$ ");
        fgets(command, sizeof(command), stdin);

        /* Remove the newline character from the command */
        command[strcspn(command, "\n")] = '\0';

        /* Check for end of file condition */
        if (feof(stdin))
        {
            printf("\n");
            break;
        }

        /* Fork a child process */
        pid = fork();

        if (pid == -1)
        {
            fprintf(stderr, "Error forking process\n");
            continue;
        }
        else if (pid == 0)
        {
            /* Child process */

            /* Execute the command */
            status = system(command);

            /* If system returns, there was an error */
            if (status == -1)
            {
                fprintf(stderr, "Error executing command\n");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        else
        {
            /* Parent process */

            /* Wait for the child process to complete */
            int childStatus;
            waitpid(pid, &childStatus, 0);

            /* Check if the child process exited normally */
            if (WIFEXITED(childStatus))
            {
                int exitStatus = WEXITSTATUS(childStatus);
                if (exitStatus != 0)
                {
                    fprintf(stderr, "Command exited with status %d\n", exitStatus);
                }
            }
            else if (WIFSIGNALED(childStatus))
            {
                int signalNumber = WTERMSIG(childStatus);
                fprintf(stderr, "Command terminated with signal %d\n", signalNumber);
            }
        }
    }

    return 0;
}
