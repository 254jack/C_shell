#include "shell.h"

/**
 * h_exit - a function that handles exit command
 * @cmd: command
 */
void h_exit(char *cmd)
{
	if (strncmp(cmd, "exit ", 5) == 0)
	{
		int status;
		char *arg = cmd + 5;
		int isNumeric = 1;
		size_t arglen = strlen(arg);
		size_t i;

		for (i = 0; i < arglen; i++)
		{
			if (!isdigit((unsigned char)arg[i]))
			{
				isNumeric = 0;
				break;
			}
		}

		if (isNumeric)
		{
			status = atoi(arg);
			free(cmd);
			_Exit(status);
		}
		else
		{
			fprintf(stderr, "./hsh: 1: exit: Illegal number: %s\n", arg);
			free(cmd);
			_Exit(2);
		}
	}
	else if (strcmp(cmd, "exit") == 0)
	{
		free(cmd);
		_Exit(EXIT_SUCCESS);
	}
}
