#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0 on success.
 */
int main(void)
{
    char *input;
    int status;

    while (1)
    {
        print_prompt();
        input = read_line();

        if (input == NULL)
        {
            free(input);
            break;
        }

        status = execute_command(input);

        free(input);

        if (status == EXIT_SHELL)
            break;
    }

    return (0);
}

/**
 * read_line - Read a line of input from the user
 *
 * Return: A pointer to the input string.
 */
char *read_line(void)
{
    char *input = NULL;
    size_t bufsize = 0;

    if (getline(&input, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        {
            printf("\n"); /* Print a new line before exiting on Ctrl+D */
            return NULL;
        }
        else
        {
            perror("read_line");
            exit(EXIT_FAILURE);
        }
    }

    return input;
}

/**
 * execute_command - Execute the given command
 * @command: The command to execute
 *
 * Return: The status code of the command.
 */
int execute_command(char *command)
{
    int status = 0;
    char *token;
    char **args;
    int i = 0;

    /* Tokenize the command to get individual arguments */
    args = malloc(sizeof(char *) * ARG_MAX);
    if (!args)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(command, " \t\n");
    while (token != NULL)
    {
        args[i++] = strdup(token);
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;

    /* Execute the command */
    if (args[0] != NULL)
    {
        if (strcmp(args[0], "exit") == 0)
            status = EXIT_SHELL;
        else if (strcmp(args[0], "cd") == 0)
            status = execute_cd(args);
        else if (strcmp(args[0], "env") == 0)
            status = execute_env();
        else
            status = execute_external(args);
    }

    /* Free the allocated memory */
    for (i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);

    return status;
}

/**
 * print_prompt - Print the shell prompt
 */
void print_prompt(void)
{
    printf("#cisfun$ ");
}
