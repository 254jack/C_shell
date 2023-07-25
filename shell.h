#ifndef SHELL_H
#define SHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX_CMD_LENGTH 100
#define MAX_ARGUMENTS 10


int prompt(void);
void split_arguments(const char *cmd, char *args[], int *argc);
int execute(const char *cmd);

#endif
