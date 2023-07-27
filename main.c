#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
* main - the main function entry point of the program
* @argc: argument count
* @argv: arg vector
* @env: environment variable
*
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
