#include "shell.h"
/**
* split_arguments - a function that
* tokenizes user inputed commands to arguments
* @cmd - command
* @args- arguments
* @argc- arguments count
* Return: 0
*/
void split_arguments(const char *cmd, char *args[], int *argc)
{
*argc = 0;


char *token = strtok((char *)cmd, " ");


while (token != NULL && *argc < MAX_ARGUMENTS - 1)
{
args[*argc] = token;
(*argc)++;
token = strtok(NULL, " ");
}
args[*argc] = NULL;
}


