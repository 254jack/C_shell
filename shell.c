#include "shell.h"

#define MAX_ARGS 10

/**
 * prompt - a function that displays a prompt and executes user cmds
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
			free(cmd);
			exit(EXIT_SUCCESS);
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
 * executeCmd - a function that executes a cmd using execve.
 * @cmd: The cmd to execute
 * @argv: The arguments for the cmd
 * @env: The environment variable
 */
void executeCmd(char *cmd, char **argv, char **env)
{
	char **env_ptr = env;
	char *path = getenv("PATH");
	char *token = strtok(path, ":");
	(void)cmd;

	if (strcmp(argv[0], "env") == 0)
	{
		while (*env_ptr != NULL)
		{
			printf("%s\n", *env_ptr);
			env_ptr++;
		}
		return;
	}

	while (token != NULL)
	{
		char *cmd = malloc(strlen(token) + strlen(argv[0]) + 2);
		sprintf(cmd, "%s/%s", token, argv[0]);

		if (access(cmd, X_OK) == 0)
		{
			pid_t c_pid = fork();
			if (c_pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (c_pid == 0)
			{
				execve(cmd, argv, env);
				perror("execve");
				free(cmd);
				exit(EXIT_FAILURE);
			}
			else
			{
				int status;
				wait(&status);
				free(cmd);
				return;
			}
		}

		free(cmd);
		token = strtok(NULL, ":");
	}
	fprintf(stderr, "%s: cmd not found\n", argv[0]);
}
