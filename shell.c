#include "shell.h"
#define MAX_ARGS 10

void prompt(char **av, char **env);
void lid_ln(char *str);
void tokenizeCmd(char *cmd, char **argv);
void executeCmd(char *cmd, char **argv, char **env);
void exc_e_cmd(char *cmd, char **argv, char **env);
void search_exc(char *cmd, char **argv, char **env);

/**
 * prompt - Displays a prompt and executes user cmds
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
		search_exc(av[0], argv, env);

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
		argv[p++] = strtok(NULL, " ");
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
	pid_t c_pid;
	int status;

	(void)cmd;

	if (strcmp(argv[0], "env") == 0)
	{
		char **env_ptr = env;

		while (*env_ptr != NULL)
		{
			printf("%s\n", *env_ptr);
			env_ptr++;
		}
		return;
	}

	c_pid = fork();
	if (c_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (c_pid == 0)
	{
		exc_e_cmd(argv[0], argv, env);
	}
	else
	{
		wait(&status);
	}
}

/**
 * exc_e_cmd - a function that executes an external command using execve.
 * @cmd: The cmd to execute
 * @argv: The arguments for the cmd
 * @env: The environment variable
 */
void exc_e_cmd(char *cmd, char **argv, char **env)
{
	if (execve(argv[0], argv, env) == -1)
	{
		search_exc(cmd, argv, env);
	}
	exit(EXIT_FAILURE);
}

/**
 * search_exc - a function that searches for
 * and executes a command in the PATH.
 * @cmd: The cmd to execute
 * @argv: The arguments for the cmd
 * @env: The environment variable
 */
void search_exc(char *cmd, char **argv, char **env)
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");

	while (token != NULL)
	{
		char *cmd_path = malloc(strlen(token) + strlen(cmd) + 2);

		sprintf(cmd_path, "%s/%s", token, cmd);

		if (access(cmd_path, X_OK) == 0)
		{
			exc_e_cmd(cmd_path, argv, env);
		}

		free(cmd_path);
		token = strtok(NULL, ":");
	}

	printf("%s: No such file or directory\n", cmd);
	exit(EXIT_FAILURE);
}
