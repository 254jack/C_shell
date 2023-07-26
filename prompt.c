#include "shell.h"

/**
 * inter_md - a function that
 * enters the prompt to iteractive mode
 * Return: 0
 */
int inter_md(void)
{
	return (isatty(STDIN_FILENO));
}
/**
 * prompt - a function that displays a
 *command line for user to type in commands
 * Return: 0
 */
int prompt(void)
{
	char cmd[MAX_CMD_LENGTH];

	if (inter_md())
	{
		printf("#cisfun$ ");
	}

	if (fgets(cmd, sizeof(cmd), stdin) == NULL)
	{
		if (feof(stdin))
		{
			if (inter_md())
				printf("\n");
			return (-1);
		}
		perror("fgets");
		return (0);
	}

	cmd[strcspn(cmd, "\n")] = '\0';

	return (execute(cmd));
}
