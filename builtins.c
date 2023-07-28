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

		free(cmd);
		exit(status);
	}
	else if (strcmp(cmd, "exit") == 0)
	{
		free(cmd);
		exit(EXIT_SUCCESS);
	}
}
