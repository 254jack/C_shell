#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

int main(int ac, char **av, char **env)
{
    if (ac == 1)
    {
        prompt(av, env); 
    }
    return 0;
}
