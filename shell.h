#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10
void lid_ln(char *str);
void tokenizeCmd(char *cmd, char **argv);
void executeCmd(char *cmd, char **argv, char **env);

void prompt(char **av, char **env);
#endif