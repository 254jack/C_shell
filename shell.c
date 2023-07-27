#include "shell.h"

/**
 * prompt - Displays a prompt and executes user commands
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
		printf("Cisfun$ ");
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

		removeNewline(cmd);
		tokenizeCommand(cmd, argv);

		executeCommand(av[0], argv, env);

		free(cmd);
		cmd = NULL;
	}
}

/**
 * removeNewline - Removes the newline character from a string
 * @str: The string to modify
 */
void removeNewline(char *str)
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
 * tokenizeCommand - Tokenizes a command string into arguments
 * @cmd: The command string to tokenize
 * @argv: The array to store the arguments
 */
void tokenizeCommand(char *cmd, char **argv)
{
	int p = 0;

	argv[p] = strtok(cmd, " ");
	while (argv[p])
	{
		argv[++p] = strtok(NULL, " ");
	}
}

/**
 * executeCommand - Executes a command using execve
 * @cmd: The command to execute
 * @argv: The arguments for the command
 * @env: The environment variable
 */
void executeCommand(char *cmd, char **argv, char **env)
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
