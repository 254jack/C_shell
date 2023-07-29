#include "shell.h"
#define MAX_ARGS 10

/**
 * prompt - Displays a prompt and executes user cmds
 * prompt - a function that displays a prompt and executes user cmds
 * @av: Argument vector
 * @env: Environment variable
 */
void prompt(char **av, char **env)
{
	char *cmd = NULL;
	char old_dir[PATH_MAX] = "";
	char new_dir[PATH_MAX] = "";
	size_t n = 0;
	ssize_t n_char;
	char *argv[MAX_ARGS];

	while (1)
	{

		if (isatty(STDIN_FILENO))
		{
			printf("Cisfun$ ");
		}
		n_char = getline(&cmd, &n, stdin);

		if (n_char == -1)
		{
			if (feof(stdin))
			{
				free(cmd);
				exit(EXIT_SUCCESS);
			}
			else
			{
				perror("getline");
				free(cmd);
				exit(EXIT_FAILURE);
			}
		}
		if (cmd == NULL || cmd[0] == '\n')
		{
			free(cmd);
			cmd = NULL;
			continue;
		}
		lid_ln(cmd);
		h_exit(cmd);
		if (strcmp(cmd, "exit") == 0)
		{
			free(cmd);
			exit(EXIT_SUCCESS);
		}

		if (strncmp(cmd, "cd", 2) == 0)
		{
			h_cd(cmd, old_dir, new_dir);
			free(cmd);
			cmd = NULL;
			return;
		}
		tokenizeCmd(cmd, argv);
		executeCmd(av[0], argv, env);
		free(cmd);
		cmd = NULL;
	}
}
/**
 * lid_ln - a function that removes the newline
 * @str: string
 * Return: 0
 */
void lid_ln(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}
/**
 * tokenizeCmd - a function that splits the string into tokens
 * @cmd: string cmd
 * @argv: argument vector
 * Return: 0
 */
int tokenizeCmd(char *cmd, char **argv)
{
	int p = 0;

	argv[p] = strtok(cmd, " ");

	while (argv[p] != NULL && p < MAX_ARGS - 1)
	{
		p++;
		argv[p] = strtok(NULL, " ");
	}

	return p;
}
