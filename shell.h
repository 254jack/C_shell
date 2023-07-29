#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include<signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#define PATH_MAX 4096

#define MAX_ARGS 10
#define MAX_COMMANDS 100
#define _GNU_SOURCE

void prompt(char **av, char **env);
void lid_ln(char *str);
int tokenizeCmd(char *cmd, char **argv);
void executeCmd(char *cmd, char **argv, char **env);
void h_exit(char *cmd);
void h_cd(char *cmd, char *old_dir, char *new_dir);
int t_cmds(char *input, char **cmds);
int cd_cmd(char **argv);
void sgnal_h(int sig);
int setenv_cmd(char **argv);
int unsetenv_cmd(char **argv);


#endif
