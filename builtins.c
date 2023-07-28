#include "shell.h"
/**
 * h_exit - a function that handles exit command
 * @cmd: command
 */
void h_exit(char *cmd)
{
	if (strncmp(cmd, "exit ", 5) == 0)
	{
		int status = atoi(cmd + 5);

		if (status < 0)
		{
			printf("./hsh: exit: illegal number: %d\n", status);
		}
		else
		{
			exit(status);
		}
		free(cmd);
		_Exit(status);
	}
	else if (strcmp(cmd, "exit") == 0)
	{
		free(cmd);
		_Exit(EXIT_SUCCESS);
	}
}
