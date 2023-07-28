#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_ARGS 10
#define _GNU_SOURCE

void prompt(char **av, char **env);
void lid_ln(char *str);
void tokenizeCmd(char *cmd, char **argv);
void executeCmd(char *cmd, char **argv, char **env);
void h_exit(char *cmd);
void h_cd(char *cmd, char *old_dir, char *new_dir);

#endif
