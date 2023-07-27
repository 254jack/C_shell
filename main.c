#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
/**
 * main - the main function of my project
 * @argc: argument count of my project.
 * @argv: argment venctor
 * @env: environment variable
 * Return: 0
*/
int main(int argc, char **argv, char **env)
{
	if (argc == 1)
	{
		prompt(argv, env);
	}
	return (0);
}
