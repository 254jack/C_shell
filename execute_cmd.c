#include "shell.h"

Alias *alias_list = NULL;

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
	char pid_buff[24];

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
	for (i = 0; argv[i] != NULL; i++)
	{
		if (strcmp(argv[i], "$$") == 0)
		{
			pid_t pid = getpid();
			sprintf(pid_buff, "%d", pid);
			argv[i] = pid_buff;
		}
	}
	if (strcmp(argv[0], "alias") == 0)
	{
		if (argv[1] == NULL)
		{
			p_a(alias_list);
		}
		else if (strchr(argv[1], '=') != NULL)
		{
			char *name, *value;
			char *token = strtok(argv[1], "=");

			while (token != NULL)
			{
				Alias *existing_alias = f_a(alias_list, name);

				name = token;
				token = strtok(NULL, "=");
				value = token;

				if (existing_alias != NULL)
				{
					update_a(existing_alias, value);
				}
				else
				{
					add_a(&alias_list, name, value);
				}

				token = strtok(NULL, "=");
			}
		}
		else
		{
			int i = 1;
			while (argv[i] != NULL)
			{
				Alias *alias = f_a(alias_list, argv[i]);
				if (alias != NULL)
				{
					printf("alias %s='%s'\n", alias->name, alias->value);
				}
				i++;
			}
		}
		return;
	}
	if (strcmp(argv[0], "env") == 0)
	{
		exc_env_cmd(env);
		return;
	}
	if (strcmp(argv[0], "cd") == 0)
	{
		cd_cmd(argv);
		return;
	}
	else if (strcmp(argv[0], "setenv") == 0)
	{
		setenv_cmd(argv);
		return;
	}
	else if (strcmp(argv[0], "unsetenv") == 0)
	{
		unsetenv_cmd(argv);
		return;
	}
	if (strcmp(argv[0], "exit") == 0)
	{
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		r_vars(argv, WEXITSTATUS(status));

		c_pid = fork();
	}
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
			fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
			exit(127);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		r_vars(argv, WEXITSTATUS(status));
		d_a(alias_list);
		waitpid(c_pid, &status, 0);
		r_vars(argv, status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
			status = 2;
	}
}