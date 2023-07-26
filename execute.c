#include "shell.h"
/**
 * execute - the function to execute a command
 * @cmd: command to execute
 *
 * Return: 0.
 */

int execute(const char *cmd)
{
	if (access(cmd, X_OK) == 0)
	{
		pid_t pid;
		char *args[MAX_ARGUMENTS];
		int argc = 0;

		char *token = strtok((char *)cmd, " ");

		while (token != NULL && argc < MAX_ARGUMENTS - 1)
		{
			args[argc++] = token;
			token = strtok(NULL, " ");
		}
		args[argc] = NULL;

		pid = fork();

		if (pid == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("Execution failed");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}
	else
	{
		printf("./shell: No such file or directory\n");
	}

	return (0);
}
