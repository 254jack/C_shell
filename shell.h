#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#define PATH_MAX 4096

#define MAX_ARGS 10
#define MAX_COMMANDS 100
#define _GNU_SOURCE

typedef struct Alias
{
    char *name;
    char *value;
    struct Alias *next;
} Alias;

void p_a(Alias *alias_list);
Alias *f_a(Alias *alias_list, const char *name);
void add_a(Alias **alias_list, const char *name, const char *value);
void update_a(Alias *alias, const char *value);
void d_a(Alias *alias_list);

void prompt(char **av, char **env);
void lid_ln(char *str);
int tokenizeCmd(char *cmd, char **argv);
void executeCmd(char *cmd, char **argv, char **env);
void h_exit(char *cmd);
int t_cmds(char *input, char **cmds);
void sgnal_h(int sig);
int setenv_cmd(char **argv);
int unsetenv_cmd(char **argv);
int cd_cmd(char **argv);
void r_vars(char **argv, int status);

#endif
