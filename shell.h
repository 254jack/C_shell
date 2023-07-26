#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define EXIT_SHELL 10
#define ARG_MAX 64

int main(void);
char *read_line(void);
int execute_command(char *command);
int execute_cd(char **args);
int execute_env(void);
int execute_external(char **args);
void print_prompt(void);

#endif /* SHELL_H */
