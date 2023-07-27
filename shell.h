#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10

/**
 * Removes the newline character from a string.
 * @param str The string to modify
 */
void removeNewline(char *str);

/**
 * Tokenizes a command string into arguments.
 * @param cmd The command string to tokenize
 * @param argv The array to store the arguments
 */
void tokenizeCommand(char *cmd, char **argv);

/**
 * Executes a command using execve.
 * @param cmd The command to execute
 * @param argv The arguments for the command
 * @param env The environment variable
 */
void executeCommand(char *cmd, char **argv, char **env);

void prompt(char **av, char **env);
#endif