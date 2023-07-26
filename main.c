#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
* main - the main function entry point of the program
* @ac: argument count
* @av: arg vector
* @env: environment variable
*
* Return: 0
*/
int main(int ac, char **av, char **env)
{
	if (ac == 1)
	{
		prompt(av, env);
	}
	return (0);
}
