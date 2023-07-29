#include "shell.h"

/**
 * exc_env_cmd - Executes the "env" command
 * and prints the environment variables.
 * @env: The environment variables.
 */
void exc_env_cmd(char **env)
{
	char **env_ptr = env;

	while (*env_ptr != NULL)
	{
		printf("%s\n", *env_ptr);
		env_ptr++;
	}
}

/**
 * exc_Exa - Executes the given extra file.
 * @extra: The name of the extra file.
 * @argv: The arguments for the extra.
 * @env: The environment variables.
 */
void exc_Exa(char *extra, char **argv, char **env)
{
	char *cmd_path = NULL;
	char *path = getenv("PATH");
	char *token = strtok(path, ":");

	while (token != NULL)
	{
		cmd_path = malloc(strlen(token) + strlen(extra) + 2);
		if (cmd_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		sprintf(cmd_path, "%s/%s", token, extra);

		if (access(cmd_path, X_OK) == 0)
		{
			execve(cmd_path, argv, env);
			free(cmd_path);
			exit(EXIT_FAILURE);
		}

		free(cmd_path);
		token = strtok(NULL, ":");
	}
}

/**
 * executeCmd - a function that executes a command using execve.
 * @cmd: command
 * @argv: argument vector
 * @env: environment variables.
 */
void executeCmd(char *cmd, char **argv, char **env)
{
	pid_t c_pid;
	int i;
	int all_empty = 1;
	int status;
	(void)cmd;

	for (i = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] != '\0')
		{
			all_empty = 0;
			break;
		}
	}

	if (all_empty)
	{
		return;
	}

	if (strcmp(argv[0], "env") == 0)
	{
		exc_env_cmd(env);
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
		if (execve(argv[0], argv, env) == -1)
		{
			exc_Exa(argv[0], argv, env);
			perror("./hsh");
			exit(127);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}