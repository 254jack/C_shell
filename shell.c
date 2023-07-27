#include "shell.h"
/**
 * prompt - Displays a prompt and executes user commands
 * @av: Argument vector
 * @env: Environment variable
 */
void prompt(char **av, char **env)
{
	char *cmd = NULL;
	int i, status, p;
	size_t n = 0;
	ssize_t n_char;
	char *argv[MAX_ARGS];
	pid_t c_pid;

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

		i = 0;

		while (cmd[i])
		{
			if (cmd[i] == '\n')
				cmd[i] = 0;
			i++;
		}
		p = 0;
		argv[p] = strtok(cmd, " ");
		while (argv[p])
		{
			argv[++p] = strtok(NULL, " ");
		}
		c_pid = fork();
		if (c_pid == -1)
		{
			free(cmd);
			exit(EXIT_FAILURE);
		}
		if (c_pid == 0)
		{
			if (execve(argv[0], argv, env) == -1)
			{
				printf("%s: No such file or directory\n", av[0]);
			}
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}

		free(cmd);
		cmd = NULL;
	}
}
