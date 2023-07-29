#include "shell.h"
/**
 * main - the main function of the project
 * @argc: argument count
 * @argv: argument vector
 * @env: environment varaible
 * Return: 0
 */
int main(int argc, char **argv, char **env)
{
	signal(SIGINT, sgnal_h);
	(void)argc;
	prompt(argv, env);
	return (EXIT_SUCCESS);
}

void sgnal_h(int sig)
{
	(void)sig;

	printf("Received SIGINT (Ctrl-C)\n");
	exit(EXIT_SUCCESS);
}
