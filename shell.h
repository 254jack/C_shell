#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 * Maximum command length
*/
#define MAX_CMD_LENGTH 100
/**
 * Maximum arguments
*/
#define MAX_ARGUMENTS 10
/**
 * prompt - a function that handles the prompt and read user input
 *
 * Return: 0
 */
int prompt(void);


int execute(const char *cmd);

#endif 
