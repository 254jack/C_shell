#include "shell.h"
/**
 * prompt - Displays a prompt and executes user commands
 * @av: Argument vector
 * @env: Environment variable
 */
void prompt(char **av, char **env)
{
	char *string = NULL;
	int i, status;
	size_t n = 0;
	ssize_t n_char;
	char *argv[] = {NULL, NULL};
	pid_t c_pid;

	while (1)
	{
		printf("Cisfun$ ");
		n_char = getline(&string, &n, stdin);

		if (n_char == -1)
		{
			if (feof(stdin))
			{
				free(string);
				exit(EXIT_SUCCESS);
			}
			else
			{
				perror("getline");
				free(string);
				exit(EXIT_FAILURE);
			}
		}

		i = 0;

		while (string[i])
		{
			if (string[i] == '\n')
				string[i] = 0;
			i++;
		}

		c_pid = fork();
		argv[0] = string;
		if (c_pid == -1)
		{
			free(string);
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

		free(string);
		string = NULL;
	}
}
