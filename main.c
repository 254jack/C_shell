#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
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
	(void)argc;
	prompt(argv, env);
	return (EXIT_SUCCESS);
}

