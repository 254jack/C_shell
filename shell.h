#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10
#define _GNU_SOURCE

void prompttt(char **av, char **env);
void lid_ln(char *str);
void tokenizeCmd(char *cmd, char **argv);
void executeCmd(char *cmd, char **argv, char **env);
void h_exit(char *cmd);

#endif
