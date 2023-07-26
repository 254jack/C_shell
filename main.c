#include "shell.h"
#include <stdio.h>

/**
 * main - The main program
 * @argc - argument count
 * @argv - argument vector
 * Return: 1.
 */
int main(int argc, char *argv[])
{
	char line[MAX_CMD_LENGTH];

	if (argc == 1)
	{
		while (1)
		{
			if (prompt() == -1)
				break;
		}
	}
	else if (argc == 2)
	{
		FILE *file = fopen(argv[1], "r");

		if (file == NULL)
		{
			perror("Error opening file");
			return (1);
		}

		while (fgets(line, sizeof(line), file))
		{
			line[strcspn(line, "\n")] = '\0';
			execute(line);
		}

		fclose(file);
	}
	else
	{
		printf("Usage: %s [script_file]\n", argv[0]);
		return (1);
	}

	return (0);
}
