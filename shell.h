#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10
/**
  *removes the new line charatcter from the string.
  *@param str the string to modify
**/

void prompt(char **av, char **env);
/**
  tokenize cmd string to tokenize arguments
  *@param cmd The command string to tokenize
 * @param argv The
 * Description: array to store the arguments
**/
#endif
