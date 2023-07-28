#include "shell.h"
/**
 * h_exit - a function that handles exit command
 * @cmd: command
 */
void h_exit(char *cmd)
{
	if (strcmp(cmd, "exit") == 0)
	{

		free(cmd);
		exit(EXIT_SUCCESS);
	}
}
