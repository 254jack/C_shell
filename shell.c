#include "shell.h"

/**
 * prompt - Displays a prompt and executes user Cmds
 * @av: Argument vector
 * @env: Environment variable
 */
void prompt(char **av, char **env)
{
	char *cmd = NULL;
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

		lid_ln(cmd);
		if (strcmp(cmd, "exit") == 0)
		{
			break;
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
 * @cmd: string command
 * @argv: argument vector
 * Return: 0
 */
void tokenizeCmd(char *cmd, char **argv)
{
	int p = 0;

	argv[p] = strtok(cmd, " ");
	while (argv[p])
	{
		argv[++p] = strtok(NULL, " ");
	}
}

/**
 * executeCmd - a function that executes a Cmd using execve.
 * @cmd: The Cmd to execute
 * @argv: The arguments for the Cmd
 * @env: The environment variable
 */
void executeCmd(char *cmd, char **argv, char **env)
{
	pid_t c_pid;
	int status;

	c_pid = fork();
	if (c_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (c_pid == 0)
	{
		if (execve(argv[0], argv, env) == -1)
		{
			printf("%s: No such file or directory\n", cmd);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}
